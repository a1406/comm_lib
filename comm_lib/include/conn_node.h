#ifndef _CONN_NODE_H__
#define _CONN_NODE_H__

#include "server_proto.h"
#include <string.h>
#include <stdint.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <event2/event_struct.h>
#include <map>

//前面已经定义了resp，直接打包发送
#define FAST_SEND_TO_CLIENT(MSGID, PACK_FUNC) \
	size_t size = PACK_FUNC(&resp, get_send_data());					\
	if (size != (size_t)-1) {													\
		PROTO_HEAD *head = get_send_buf(MSGID, 0);						\
		head->len = htons(sizeof(PROTO_HEAD) + size);					\
		add_extern_data(head, extern_data);								\
		ret = connecter.send_one_msg(head, 1);							\
		if (ret != htons(head->len)) {									\
			LOG_ERR("%s: send to client failed err[%d]", __FUNCTION__, errno); \
		}																\
	}

//在别的模块打包resp，然后发送
#define FAST_SEND_TO_CLIENT2(MSGID, PACK_FUNC) \
	size_t size = PACK_FUNC(get_send_data());							\
	if (size != (size_t)-1) {													\
		PROTO_HEAD *head = get_send_buf(MSGID, 0);						\
		head->len = htons(sizeof(PROTO_HEAD) + size);					\
		add_extern_data(head, extern_data);								\
		ret = connecter.send_one_msg(head, 1);							\
		if (ret != htons(head->len)) {									\
			LOG_ERR("%s: send to client failed err[%d]", __FUNCTION__, errno); \
		}																\
	}

//在别的模块打包resp，然后发送，多一个参数传递
#define FAST_SEND_TO_CLIENT3(MSGID, PACK_FUNC, PARAM)							\
	size_t size = PACK_FUNC(get_send_data(), PARAM);					\
	if (size != (size_t)-1) {											\
		PROTO_HEAD *head = get_send_buf(MSGID, 0);						\
		head->len = htons(sizeof(PROTO_HEAD) + size);					\
		add_extern_data(head, extern_data);								\
		ret = connecter.send_one_msg(head, 1);							\
		if (ret != htons(head->len)) {									\
			LOG_ERR("%s: send to client failed err[%d]", __FUNCTION__, errno); \
		}																\
	}


//在别的模块打包resp，然后发送，多二个参数传递
#define FAST_SEND_TO_CLIENT4(MSGID, PACK_FUNC, PARAM1, PARAM2)			\
	size_t size = PACK_FUNC(get_send_data(), PARAM1, PARAM2);					\
	if (size != (size_t)-1) {											\
	PROTO_HEAD *head = get_send_buf(MSGID, 0);						\
	head->len = htons(sizeof(PROTO_HEAD) + size);					\
	add_extern_data(head, extern_data);								\
	ret = connecter.send_one_msg(head, 1);							\
	if (ret != htons(head->len)) {									\
	LOG_ERR("%s: send to client failed err[%d]", __FUNCTION__, errno); \
	}																\
	}

//在别的模块打包resp，然后发送
#define FAST_SEND_TO_CLIENT5(MSGID, PACK_FUNC, PARAM1, PARAM2, PARAM3) \
	size_t size = PACK_FUNC(get_send_data(), PARAM1, PARAM2, PARAM3);  \
	if (size != (size_t)-1) {										\
	PROTO_HEAD *head = get_send_buf(MSGID, 0);						\
	head->len = htons(sizeof(PROTO_HEAD) + size);					\
	add_extern_data(head, extern_data);								\
	ret = connecter.send_one_msg(head, 1);							\
	if (ret != htons(head->len)) {									\
	LOG_ERR("%s: send to client failed err[%d]", __FUNCTION__, errno); \
	}																\
	}

//////////////////
//前面已经定义了resp，直接打包发送
#define SO_FAST_SEND_TO_CLIENT(CONN, MSGID, PACK_FUNC)					\
	size_t size = PACK_FUNC(&resp, CONN->get_send_data());					\
	if (size != (size_t)-1) {													\
		PROTO_HEAD *head = CONN->get_send_buf(MSGID, 0);						\
		head->len = htons(sizeof(PROTO_HEAD) + size);					\
		CONN->add_extern_data(head, extern_data);								\
		ret = CONN->connecter.send_one_msg(head, 1);							\
		if (ret != htons(head->len)) {									\
			LOG_ERR("%s: send to client failed err[%d]", __FUNCTION__, errno); \
		}																\
	}

//在别的模块打包resp，然后发送
#define SO_FAST_SEND_TO_CLIENT2(MSGID, PACK_FUNC) \
	size_t size = PACK_FUNC(&resp, CONN->get_send_data());							\
	if (size != (size_t)-1) {													\
		PROTO_HEAD *head = CONN->get_send_buf(MSGID, 0);						\
		head->len = htons(sizeof(PROTO_HEAD) + size);					\
		CONN->add_extern_data(head, extern_data);								\
		ret = CONN->connecter.send_one_msg(head, 1);							\
		if (ret != htons(head->len)) {									\
			LOG_ERR("%s: send to client failed err[%d]", __FUNCTION__, errno); \
		}																\
	}

//在别的模块打包resp，然后发送，多一个参数传递
#define SO_FAST_SEND_TO_CLIENT3(MSGID, PACK_FUNC, PARAM)							\
	size_t size = PACK_FUNC(&resp, CONN->get_send_data(), PARAM);					\
	if (size != (size_t)-1) {											\
		PROTO_HEAD *head = CONN->get_send_buf(MSGID, 0);						\
		head->len = htons(sizeof(PROTO_HEAD) + size);					\
		CONN->add_extern_data(head, extern_data);								\
		ret = CONN->connecter.send_one_msg(head, 1);							\
		if (ret != htons(head->len)) {									\
			LOG_ERR("%s: send to client failed err[%d]", __FUNCTION__, errno); \
		}																\
	}


//在别的模块打包resp，然后发送，多二个参数传递
#define SO_FAST_SEND_TO_CLIENT4(MSGID, PACK_FUNC, PARAM1, PARAM2)			\
	size_t size = PACK_FUNC(&resp, CONN->get_send_data(), PARAM1, PARAM2);					\
	if (size != (size_t)-1) {											\
	PROTO_HEAD *head = CONN->get_send_buf(MSGID, 0);						\
	head->len = htons(sizeof(PROTO_HEAD) + size);					\
	CONN->add_extern_data(head, extern_data);								\
	ret = CONN->connecter.send_one_msg(head, 1);							\
	if (ret != htons(head->len)) {									\
	LOG_ERR("%s: send to client failed err[%d]", __FUNCTION__, errno); \
	}																\
	}

//在别的模块打包resp，然后发送
#define SO_FAST_SEND_TO_CLIENT5(MSGID, PACK_FUNC, PARAM1, PARAM2, PARAM3) \
	size_t size = PACK_FUNC(&resp, CONN->get_send_data(), PARAM1, PARAM2, PARAM3);  \
	if (size != (size_t)-1) {										\
	PROTO_HEAD *head = CONN->get_send_buf(MSGID, 0);						\
	head->len = htons(sizeof(PROTO_HEAD) + size);					\
	CONN->add_extern_data(head, extern_data);								\
	ret = CONN->connecter.send_one_msg(head, 1);							\
	if (ret != htons(head->len)) {									\
	LOG_ERR("%s: send to client failed err[%d]", __FUNCTION__, errno); \
	}																\
	}


#define MAX_BUF_PER_CLIENT (128 * 1024 - 1 - sizeof(EXTERN_DATA))
class conn_node_base
{
public:
	conn_node_base();
	virtual ~conn_node_base();

	virtual int recv_func(evutil_socket_t fd) = 0;
	virtual int send_one_msg(PROTO_HEAD *head, uint8_t force);	
	virtual struct event* get_write_event() { return NULL; }
	
	struct event event_recv;
	evutil_socket_t fd;
	struct sockaddr_in sock;
	uint32_t pos_begin;	
	uint32_t pos_end;	
	uint8_t buf[MAX_BUF_PER_CLIENT + sizeof(EXTERN_DATA)];

	static inline PROTO_HEAD *get_send_buf(uint16_t msg_id, uint16_t seq)
	{
		PROTO_HEAD *head = (PROTO_HEAD *)global_send_buf;
		head->msg_id = htons(msg_id);
		head->seq = seq;
		return head;
	}

	static inline uint8_t *get_send_data()
	{
		PROTO_HEAD *head = (PROTO_HEAD *)global_send_buf;
		return (uint8_t *)&head->data[0];
	}
	
	static inline void add_extern_data(PROTO_HEAD *head, EXTERN_DATA *data)
	{
		EXTERN_DATA *extern_data;
		int old_len = htons(head->len);
		int old_crc = htonl(head->crc);
		if (old_len == 0)
			extern_data = (EXTERN_DATA *)(&head->data[0] + old_crc - sizeof(PROTO_HEAD));
		else
			extern_data = (EXTERN_DATA *)(&head->data[0] + old_len - sizeof(PROTO_HEAD));
		memcpy(extern_data, data, sizeof(EXTERN_DATA));

		if (old_len == 0)
			head->crc = htonl(old_crc + sizeof(EXTERN_DATA));
		else
			head->len = htons(old_len + sizeof(EXTERN_DATA));
	}
	static uint8_t global_send_buf[MAX_BUF_PER_CLIENT + sizeof(EXTERN_DATA)];
//protected:

	uint32_t get_real_head_len(PROTO_HEAD *head);
	
	inline int buf_size() {
		return pos_end - pos_begin;
	}
	inline uint8_t * buf_head() { 
		return buf + pos_begin;
	}
	inline uint8_t * buf_tail() { 
		return buf + pos_end;
	}
	inline int buf_leave() { 
		return MAX_BUF_PER_CLIENT - pos_end;
	}

	inline int get_cmd()
	{
		PROTO_HEAD *head;
		head = get_head();
		return htons(head->msg_id);
	}
	inline PROTO_HEAD *get_head()
	{
		return (PROTO_HEAD *)buf_head();		
	}
	inline int get_len()
	{
		PROTO_HEAD *head;
		head = get_head();
		return head->len;
	}
	inline uint8_t *get_data()
	{
		PROTO_HEAD *head;
		head = get_head();
		return (uint8_t *)&head->data[0];
	}
	inline uint16_t get_seq()
	{
		PROTO_HEAD *head;
		head = get_head();
		return head->seq;
	}
	inline int get_data_len()
	{
		return get_real_head_len(get_head()) - sizeof(PROTO_HEAD) - sizeof(EXTERN_DATA);
	}

	inline EXTERN_DATA *get_extern_data(PROTO_HEAD *head)
	{
		return (EXTERN_DATA *)(&head->data[get_real_head_len(head) - sizeof(PROTO_HEAD) - sizeof(EXTERN_DATA)]);
	}

	inline bool is_full_packet();

	int get_one_buf();
	int remove_one_buf();	
};



#endif
