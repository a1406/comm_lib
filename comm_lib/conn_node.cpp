#include "conn_node.h"
#include "game_event.h"
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <string.h>

conn_node_base::conn_node_base()
{
	fd = 0;
	pos_begin = pos_end = 0;
}

conn_node_base::~conn_node_base()
{
}

uint8_t conn_node_base::global_send_buf[MAX_BUF_PER_CLIENT + sizeof(EXTERN_DATA)];
#ifdef CALC_NET_MSG
uint32_t send_buf_times[CS__MESSAGE__ID__MAX_MSG_ID];
uint32_t recv_buf_times[CS__MESSAGE__ID__MAX_MSG_ID];
uint32_t send_buf_size[CS__MESSAGE__ID__MAX_MSG_ID];
uint32_t recv_buf_size[CS__MESSAGE__ID__MAX_MSG_ID];
#endif

int conn_node_base::send_one_msg(PROTO_HEAD *head, uint8_t force)
{
	static int seq = 1;
	int ret;
	int send_num = 0;
//	head->time_stamp = time(NULL);
	char *p = (char *)head;
//	int len = htons(head->len);
	int len = get_real_head_len(head);
	head->seq = htons(seq++);
	for (;;) {
		ret = send(fd, p, len, 0);
		assert(ret <= len);
		if (ret == len)
			goto done;
		if (ret < 0) {
				//force可能会导致bug，如果一个数据包发送了一半然后发生eagain，这个时候如果失败可能导致后续的数据包错误
			if (errno != EAGAIN)// || force)  
				goto fail;
				//ignore EINPROGRESS
			usleep(100000);			
		} else if (ret < len) {
			len -= ret;
			p += ret;
			send_num += ret;
			usleep(100000);
		}
	}
done:
	if (head->msg_id != 0)
		LOG_DEBUG("%s %d: send msg[%d] len[%d], seq[%d], ret [%d]", __FUNCTION__, fd, htons(head->msg_id), htons(head->len), htons(head->seq), ret);
#ifdef CALC_NET_MSG
	uint16_t id = htons(head->msg_id);
	if (id < CS__MESSAGE__ID__MAX_MSG_ID) {
		send_buf_size[id] += len;
		++send_buf_times[id];
	}
#endif	
	
//	return (htons(head->len));
	return get_real_head_len(head);
fail:
	LOG_ERR("%s fd[%d]: msg[%d] len[%u] seq[%d] ret[%d] errno[%d] send_num = %d",
		__FUNCTION__, fd, htons(head->msg_id), get_real_head_len(head), htons(head->seq), ret, errno, send_num);			
	return ret;
}

uint32_t conn_node_base::get_real_head_len(PROTO_HEAD *head)
{
//	if (!head)
//		head = (PROTO_HEAD *)buf_head();
	assert(head);
	
	uint32_t real_len;
	if (head->len == 0)
	{
		real_len = htonl(head->crc);
	}
	else
	{
		real_len = htons(head->len);
	}
	return real_len;
}

bool conn_node_base::is_full_packet()
{
	uint32_t len = buf_size();	

	if (len < sizeof(PROTO_HEAD))  //没有够一个包头
		return (false);

	PROTO_HEAD *head = (PROTO_HEAD *)buf_head();	
	uint32_t real_len = get_real_head_len(head);
	if (len >= real_len)
		return true;
	return false;
}

//返回0表示接收完毕，返回大于0表示没接收完毕。返回小于零表示断开
int conn_node_base::get_one_buf()
{
	int ret = -1;
	PROTO_HEAD *head;
	int len;

	if (is_full_packet()) {
		len = buf_size();
		head = (PROTO_HEAD *)buf_head();
		uint32_t real_len = get_real_head_len(head);		
		if (head->msg_id != 0) {
			LOG_DEBUG("%s %d: get msg[%d] len[%u], seq[%d], max_len [%d], is full packet",
				__FUNCTION__, fd, htons(head->msg_id), real_len, htons(head->seq), len);
		}
	//	assert(htons(head->len) >= sizeof(PROTO_HEAD));
		if (real_len < sizeof(PROTO_HEAD)) {
//			remove_listen_callback_event(this);
			LOG_ERR("[%s : %d]: get data failed, size = %d", __FUNCTION__, __LINE__, real_len);
			return -1;
		}
#ifdef CALC_NET_MSG
		uint16_t id = htons(head->msg_id);
		if (id < CS__MESSAGE__ID__MAX_MSG_ID) {
			++recv_buf_times[id];
			uint32_t real_len = get_real_head_len(head);
			recv_buf_size[id] += real_len;
		}
#endif	
		return (0);
	}

	ret = recv(fd, buf_tail(), buf_leave(), 0);
	if (ret == 0) {
		LOG_INFO("%s %d %d: recv ret [%d] err [%d] buf[%p] pos_begin[%d] pos_end[%d]", __FUNCTION__, __LINE__, fd, ret, errno, buf, pos_begin, pos_end);
		return (-1);		
	}
	else if (ret < 0) {
		if (errno != EAGAIN && errno != EINTR) {
			LOG_ERR("%s %d %d: recv ret [%d] err [%d] buf[%p] pos_begin[%d] pos_end[%d]", __FUNCTION__, __LINE__, fd, ret, errno, buf, pos_begin, pos_end);			
			return (-1);
		}
		else {
			LOG_INFO("%s %d %d: recv ret [%d] err [%d] buf[%p] pos_begin[%d] pos_end[%d]", __FUNCTION__, __LINE__, fd, ret, errno, buf, pos_begin, pos_end);						
			return 2;
		}
	}
	else {
		pos_end += ret;
	}
	len = buf_size();	
	assert((int32_t)pos_end>=ret);

	if (len < (int)sizeof(PROTO_HEAD)) {  //没有够一个包头
//		LOG_INFO("[%s : %d]: packet header error, len: %d, leave: %d", __FUNCTION__, __LINE__, len, buf_leave());
		return (1);
	}

	head = (PROTO_HEAD *)buf_head();
	int real_len = get_real_head_len(head);
	if (len >= real_len) { //读完了
		if (head->msg_id != 0) {
			LOG_DEBUG("%s %d: get msg[%d] len[%u], seq[%d], max_len [%d]",
				__FUNCTION__, fd, htons(head->msg_id), real_len, htons(head->seq), len);
		}

		if (real_len < (int)sizeof(PROTO_HEAD)) {
			//			remove_listen_callback_event(this);
	//		LOG_ERR("[%s : %d]: get data failed 2, leave: %d", __FUNCTION__, __LINE__, buf_leave());
			return -1;
		}
#ifdef CALC_NET_MSG
		uint16_t id = htons(head->msg_id);
		if (id < CS__MESSAGE__ID__MAX_MSG_ID) {
			++recv_buf_times[id];			
			recv_buf_size[id] += real_len;
		}
#endif	
		return (0);
	}

	LOG_INFO("%s %d: len not enough, msg[%d] len[%d], max_len [%d], db leave: %d",	__FUNCTION__, fd, htons(head->msg_id), real_len, len, buf_leave());	
	return (1);    //没有读完
}

//返回0表示正常，返回大于0表示还有包没有处理完, 不会小于0
int conn_node_base::remove_one_buf()
{
	PROTO_HEAD *head;
	int buf_len;
	int msg_id;
	int len = buf_size();
	assert(len >= (int)sizeof(PROTO_HEAD));

	head = (PROTO_HEAD *)buf_head();
//	buf_len = htons(head->len);
	buf_len = get_real_head_len(head);
	msg_id = htons(head->msg_id);
	assert(len >= buf_len);

	if (msg_id != 0) {
		LOG_DEBUG("%s %d: msg[%d] len[%d], reset_len [%d] move_len[%d]",
			__FUNCTION__, fd, msg_id, buf_len, len, len - buf_len);
	}
	
	if (len == buf_len) {
		pos_begin = pos_end = 0;
		return (0);
	}
		
	pos_begin += buf_len;
	if (is_full_packet()) {
		return (0);
	}

	len = buf_size();
	memmove(&buf[0], buf_head(), len);
	pos_begin = 0;
	pos_end = len;

	LOG_DEBUG("%s %d: memmove happened, len = %d", __FUNCTION__, fd, len);
		
//	memmove(head,
//		head + buf_len,
//		len - buf_len);
//	pos_begin -= buf_len;	
//	pos_end -= buf_len;
	return (1);
	
//	head = (PROTO_HEAD *)buf_head();
	
//	len = buf_size();

//	LOG_DEBUG("%s %d: msg[%d] len[%d], reset_len [%d] move_len[%d]",
//		__FUNCTION__, fd, msg_id, buf_len, len, len - buf_len);		
	
//	if (len >= (int)sizeof(PROTO_HEAD)
//		&& len >= htons(head->len))
//		return (1);
//	return (0);
}

