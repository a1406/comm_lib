
#ifndef redis_client_h_
#define redis_client_h_

#include <hiredis/hiredis.h>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <strings.h>
#include <assert.h>
#include <vector>
#include <stdint.h>
#include <sstream>
#include "stl_relation.h"
#include "game_event.h"

class CAutoRedisReply
{
public:
	CAutoRedisReply(redisReply* r = NULL)
		: m_r(r) {}

	~CAutoRedisReply() {
		if (m_r)
		{
			freeReplyObject(m_r);
			m_r = NULL;
		}
	}

public:
	void set(redisReply* r)
	{
		if (m_r)
		{
			freeReplyObject(m_r);
			m_r = NULL;
		}

		m_r = r;
	}

	redisReply* get()
	{
		return m_r;
	}

private:
	CAutoRedisReply operator=(const CAutoRedisReply&);
	CAutoRedisReply (const CAutoRedisReply&);	

private:
	redisReply* m_r;
};

class CRedisClient
{
public:
	CRedisClient()
		: m_isConnect(false)
		, m_redisCtx(NULL){}

	virtual ~CRedisClient()
	{
		clear();
	}

public:
	int connect(const char* szIP, int port, int timeout=5000) {
		if (!szIP || port<=0) 
			return -1;

		m_szIp = std::string(szIP);
		m_nPort = port;
		m_timeout = timeout;	

		return connect();
	}

	///@ ����ֵ��ȡdb��С
	///@ param[in]	table��ֵ
	///@ result: >=0: success,<0ʧ��
	int size(const char* table)
	{
		if (!table) 
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		char buffer[4096] = {0};
		snprintf(buffer, sizeof(buffer), "HLEN %s", table);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);

	//	if (!(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str,"OK") == 0))
		if (r->type!=REDIS_REPLY_INTEGER)
			return -3;

		return r->integer;
	}

	///@ ����ֵ�ж�key�Ƿ����
	///@ param[in]  table��ֵ
	///@ param[in]  playerid
	///@ result: >0-����; 0-������, <0-����
	int exist(const char* table, uint64_t playerid)
	{
		if (!table) 
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		char buffer[4096] = {0};
		snprintf(buffer, sizeof(buffer), "HEXISTS %s %.0f", table, (double)playerid);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);

		//	if (!(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str,"OK") == 0))
		if (r->type!=REDIS_REPLY_INTEGER) 
			return -3;

		return r->integer;
	}

	///@ ����ֵ�ж�key�Ƿ����
	///@ param[in]  table��ֵ
	///@ param[in]  key
	///@ result: >0-����; 0-������, <0-����
	int exist(const char* table, const char* key)
	{
		if (!table || !key) 
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		char buffer[4096] = {0};
		snprintf(buffer, sizeof(buffer), "HEXISTS %s %s", table, key);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);

		//	if (!(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str,"OK") == 0))
		if (r->type!=REDIS_REPLY_INTEGER) 
			return -3;

		return r->integer;
	}

	int hset_bin(const char* table, const char* key, const char* val, const int val_len)
	{
		if (!table || !key || !val)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}
		const char *cmd[10];
		size_t  len[10];
		cmd[0] = "HSET";
		len[0] = strlen(cmd[0]);
		cmd[1] = table;
		len[1] = strlen(cmd[1]);
		cmd[2] = key;
		len[2] = strlen(cmd[2]);
		cmd[3] = val;
		len[3] = val_len;
		redisReply *r = (redisReply *)redisCommandArgv(m_redisCtx, 4, &cmd[0], &len[0]);
		if (!r)
		{
			return (-1);
		}

		if (r->type!=REDIS_REPLY_INTEGER)
		{
			freeReplyObject( r );
			return -2;
		}
		ret = r->integer;
		freeReplyObject( r );
		return ret;
	}

		//����������out_val�����ڴ�
	int hget_bin(const char* table, const char* key, char* out_val, int *out_len)
	{
		if (!table || !key || !out_val || !out_len)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}
		const char *cmd[10];
		size_t  len[10];
		
		cmd[0] = "HGET";
		len[0] = strlen(cmd[0]);
		cmd[1] = table;
		len[1] = strlen(cmd[1]);
		cmd[2] = key;
		len[2] = strlen(cmd[2]);
		redisReply *r = (redisReply *)redisCommandArgv(m_redisCtx, 3, &cmd[0], &len[0]);
		if (!r)
		{
			return (-1);
		}
		if (r->type!=REDIS_REPLY_STRING)
		{
			freeReplyObject( r );
			return -2;
		}
		if (*out_len < r->len)
		{
			freeReplyObject( r );
			return -3;			
		}
		
		*out_len = r->len;
		memcpy(out_val, r->str, r->len);
		freeReplyObject( r );
		return (0);
	}

		//ʹ������Ҫ�ͷ�*out_val
	int hget_bin2(const char* table, const char* key, char **out_val, int *out_len)
	{
		if (!table || !key || !out_val || !out_len)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}
		const char *cmd[10];
		size_t  len[10];
		
		cmd[0] = "HGET";
		len[0] = strlen(cmd[0]);
		cmd[1] = table;
		len[1] = strlen(cmd[1]);
		cmd[2] = key;
		len[2] = strlen(cmd[2]);
		redisReply *r = (redisReply *)redisCommandArgv(m_redisCtx, 3, &cmd[0], &len[0]);
		if (!r)
		{
			return (-1);
		}
		if (r->type!=REDIS_REPLY_STRING)
		{
			freeReplyObject( r );
			return -2;
		}

		*out_val = (char *)malloc(r->len);
		if (!(*out_len))
		{
			freeReplyObject( r );
			return -3;			
		}
		
		*out_len = r->len;
		memcpy(*out_val, r->str, r->len);
		freeReplyObject( r );
		return (0);
	}
	

	///@ ����ֵ�������
	///@ param[in]	table��ֵ
	///@ param[in]	keyֵ
	///@ param[in]	info�û���Ϣ
	///@ result: 0: success,<0ʧ��
	int set(const char* table, const char* key, const char* val, uint32_t expire_ts=0)
	{
		if (!table || !key || !val)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		char buffer[4096] = { 0 };
		snprintf(buffer, sizeof(buffer), "hset %s %s  %s", table, key, val);

		{
			CAutoRedisReply autoR;
			redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
			if (NULL == r) {
				LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
				m_isConnect = false;
				return -2;
			}

			autoR.set(r);

			if (r->type!=REDIS_REPLY_INTEGER)
				return -3;

		}

		{
			if (expire_ts > 0) {
				snprintf(buffer, sizeof(buffer), "expire %s %u", table, expire_ts);
				CAutoRedisReply autoR;
				redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
				if (NULL == r) {
					LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
					m_isConnect = false;
					return -2;
				}

				autoR.set(r);

				if (r->type!=REDIS_REPLY_INTEGER)
					return -3;
			}
		}

		return 0;
	}

	///@ ����ֵ�Ĳ������
	///@ param[in]	table��ֵ
	///@ param[in]	playerid��Ϸ���û�id
	///@ param[in]	info�û���Ϣ
	///@ result: 0: success,<0ʧ��
	int set(const char* table, uint64_t playerid, const char* data, int len, uint32_t expire_ts=0)
	{
		if (!data || !table ||len<=0) 
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		char buffer[4096] = {0};

		{
			snprintf(buffer, sizeof(buffer), "hset %s %.0f  %s", table, (double)playerid, data);

			CAutoRedisReply autoR;
			redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
			if (NULL == r) {
				LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
				m_isConnect = false;
				return -2;
			}

			autoR.set(r);

			if (r->type!=REDIS_REPLY_INTEGER)
				return -3;
		}

		{
			if (expire_ts > 0) {
				snprintf(buffer, sizeof(buffer), "expire %s %u", table, expire_ts);
				CAutoRedisReply autoR;
				redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
				if (NULL == r) {
					LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
					m_isConnect = false;
					return -2;
				}

				autoR.set(r);

				if (r->type!=REDIS_REPLY_INTEGER)
					return -3;
			}
		}

		return 0;
	}

	int set(const char* key, const char* val) {
		if (!key || !val)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		std::ostringstream os;
		os << " set " << std::string(key) << " " << std::string(val);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, os.str().c_str());
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -1;
		}

		autoR.set(r);
		if (r->type != REDIS_REPLY_INTEGER)
			return -1;

		return r->integer;
	}

	///@ �޸�����
	///@ param[in]	table�ɽ�ֵ
	///@ param[in]	newtable�½�ֵ
	///@ result: 0: success,<0ʧ��
	int rename(const char* table, const char* newtable) {
		if (!table || !newtable)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("[%s : %d]: connect redis failed", __FUNCTION__, __LINE__);
			return -1;
		}

		char cmd[64];
		snprintf(cmd, sizeof(cmd), "rename %s %s", table, newtable);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, cmd);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);

		if (r->type!=REDIS_REPLY_STATUS || !r->str || 0!=strcasecmp(r->str, "OK"))
			return -3;

		return 0;
	}
	 
	///@ ����ֵ��ȡ
	int get(const char* table, std::vector<std::relation_three<uint64_t, char*, int> >& info)
	{
		if (info.size()<=0 || !table)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		std::ostringstream os;
		os << " hmget " << std::string(table) ;

		for (size_t i=0; i<info.size(); ++i)
		{
			os << " " << info[i].first ;
		}

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, os.str().c_str());
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);

		if (r->type != REDIS_REPLY_ARRAY)
			return -3;

		for (size_t i = 0; i < r->elements; ++i) {
			std::string name;
			redisReply* childReply = r->element[i];
			if (childReply->type == REDIS_REPLY_STRING)
			{
				char* p = (char*)malloc(childReply->len+1);
				if (NULL == p) {
					for (size_t i=0; i<info.size(); ++i) {
						if (info[i].second) {
							free(info[i].second);
							info[i].second = NULL;
						}
					}
					return -4;
				}

				memcpy(p, childReply->str, childReply->len);
				info[i].second = p;
				info[i].three = childReply->len;
				p[childReply->len] = '\0';
			}
		}

		return 0;
	}

	///@ ����ֵ��ȡ
	std::string get(const char* table, const char* key)
	{
		if (!key || !table)
			return "";

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return "";
		}

		std::ostringstream os;
		os << " hget " << std::string(table) << " " << std::string(key);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, os.str().c_str());
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return "";
		}

		autoR.set(r);
		if (r->type != REDIS_REPLY_STRING)
			return "";

		return std::string(r->str);
	}

	///@ ����ֵ��ȡ
	std::string get(const char* key)
	{
		if (!key)
			return "";

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return "";
		}

		std::ostringstream os;
		os << " get " << std::string(key);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, os.str().c_str());
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return "";
		}

		autoR.set(r);
		if (r->type != REDIS_REPLY_STRING)
			return "";

		return std::string(r->str);
	}

	///@ ����ֵɾ��
	int hdel(const char* table, const std::vector<uint64_t>& info)
	{
		if (!table || info.size()<=0)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		std::ostringstream os;
		os << "hdel " << std::string(table);

		for (size_t i=0; i<info.size(); ++i)
		{
			os << " " << info[i];
		}

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, os.str().c_str());
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);

		if( r->type == REDIS_REPLY_INTEGER )
			return r->integer==1 ? 0 : -1;

		return -1;
	}

	///@ ����ֵɾ��
	int hdel(const char* table, const char* key)
	{
		if (!table || !key)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		std::ostringstream os;
		os << "hdel " << std::string(table) << " " << std::string(key);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, os.str().c_str());
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);

		if( r->type == REDIS_REPLY_INTEGER )
			return r->integer==1 ? 0 : -1;

		return -1;
	}

	///@ ����ֵɾ��
	int del(const char* key)
	{
		if (!key)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		std::ostringstream os;
		os << "del " << std::string(key);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, os.str().c_str());
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);

		if( r->type == REDIS_REPLY_INTEGER )
			return r->integer==1 ? 0 : -1;

		return -1;
	}

	///@ ��ȡSortedSet�ĳ���
	///@ param[in]	key
	///@ param[out]	out
	int zcard(const char* key, uint32_t& out) {
		char command[1024];
		if (!key) 
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		snprintf(command, sizeof(command), "zcard %s", key); /// get number of members
		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, command);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);

		if( r->type != REDIS_REPLY_INTEGER )
			return -3;

		out = (uint32_t)(r->integer);

		return 0; 
	}

	///@ ���ó�Ա����
	///@ param[in]	key
	///@ param[in]	member��Ա
	///@ param[in]	value��Աֵ
	int zset(const char* key, uint64_t member, uint32_t value) {
		char command[1024];
		if (!key || !member) 
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		uint64_t tmp = value;
		tmp <<= 32;

		uint32_t tm = (0xffffffff-(uint32_t)time(NULL));
		tmp |= (uint64_t)tm;

		snprintf(command, sizeof(command), "zadd %s %.0f %.0f", key, (double)tmp, (double)member);
		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, command);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);

		//if (!(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str,"OK") == 0))
		if (r->type != REDIS_REPLY_INTEGER)
			return -3;

		return 0;
	}

	///@ ��ȡ����
	///@ param[in]	key
	///@ param[in]	startNo��ʼ����,��0��ʼ
	///@ param[in]	endNo��������
	///@ param[out]	out�����б�vector<pair< �û���, ����> >
	int zget(const char* key, int startNo, int endNo, std::vector<std::pair<uint64_t, uint32_t> >& out) {
		char command[1024];
		if (!key) 
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		snprintf(command, sizeof(command), "ZREVRANGE %s %d %d WITHSCORES", key, startNo, endNo);
		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, command);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);
		if( r->type != REDIS_REPLY_ARRAY ) 		
			return -3;

		out.clear();
		for (size_t i = 0; i < r->elements/2; ++i) {
			uint64_t playerid;
			uint64_t score=0;
			redisReply* childReply = r->element[i*2];
			if (childReply->type == REDIS_REPLY_STRING)
				playerid = strtoull(childReply->str, NULL, 0);

			childReply = r->element[i*2+1];
			if (childReply->type == REDIS_REPLY_STRING)
				score = strtoull(childReply->str, NULL, 0);

			out.push_back(std::make_pair(playerid, (uint32_t)(score>>32)));
		}

		return 0;
	}


	///@ ��ȡ��Ա������
	///@ param[in]	key
	///@ param[in]	member��Ա
	///@ param[out]	out
	int zget_rank(const char* key, uint64_t member, uint32_t& out) {
		char command[1024];
		if (!key)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		snprintf(command, sizeof(command), "zrevrank %s %.0f", key, (double)member); 
		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, command);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);
		if (r->type != REDIS_REPLY_INTEGER)
			return -3;

		out = (uint32_t)(r->integer);

		return 0; 
	}

	///@ ��ȡ��Ա�Ļ���
	///@ param[in]	key
	///@ param[in]	member��Ա
	///@ param[out]	out
	int zget_score(const char* key, uint64_t member, uint32_t& out) {
		char command[1024];
		if (!key) 
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		snprintf(command, sizeof(command), "zscore %s %.0f", key, (double)member); /// get score
		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, command);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);

		if( r->type != REDIS_REPLY_STRING )
			return -3;

		uint64_t score = strtoull(r->str, NULL, 0);
		out = (uint32_t)(score>>32);

		return 0; 
	}

	/// ɾ��ĳ�˵�����
	int zdel(const char* key, const std::vector<uint64_t>& dellist) {
		if (!key || dellist.size()<=0)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		std::ostringstream os;
		os << " zrem " << key;

		for (size_t i=0; i<dellist.size(); ++i)
			os << "  " << dellist[i];

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, os.str().c_str());
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);
		if( !(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str,"OK")==0))
			return -3;

		return 0;
	}


	/// �������
	/// ��������β��
	int list_insert(const char* key, const char* value) {
		if (!key || !value)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		char buffer[1024] = { 0 };
		snprintf(buffer, sizeof(buffer), "lpush %s %s", key, value);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);
		if(r->type == REDIS_REPLY_INTEGER)
			return 0;

		return -1;
	}

	/// �������
	/// �޸������ֵ
	int list_set(const char* key, uint32_t idx,  const char* value) {
		if (!key || !value)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		char buffer[1024] = { 0 };
		snprintf(buffer, sizeof(buffer), "LSET %s %u %s", key, idx, value);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);
		if(r->type == REDIS_REPLY_INTEGER)
			return 0;

		return -1;
	}

	/// ��ȡָ��Ԫ��
	int list_get(const char* key, int startNo, int endNo, std::vector<std::string>& out) 
	{
		if (!key || startNo>endNo)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		char buffer[1024] = { 0 };
		snprintf(buffer, sizeof(buffer), "LRANGE %s %d %d", key, startNo, endNo);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);
		if( r->type != REDIS_REPLY_ARRAY )
			return -3;

		for (size_t i = 0; i < r->elements; ++i) {
			redisReply* childReply = r->element[i];
			if (childReply->type == REDIS_REPLY_STRING) {
				std::string tmp;
				tmp.assign(childReply->str, childReply->len);
				out.push_back(tmp);
			}
		}

		return 0;
	}

	/// ��ȡָ��Ԫ��
	int get_score(const char* key, int startScore, int endScore, std::vector<uint64_t>& out) 
	{
		if (!key || startScore>endScore)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		char buffer[1024] = { 0 };
		snprintf(buffer, sizeof(buffer), "ZREVRANGE  %s %d %d", key, startScore, endScore);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);
		if( r->type != REDIS_REPLY_ARRAY )
			return -3;

		for (size_t i = 0; i < r->elements; ++i) {
			redisReply* childReply = r->element[i];
			if (childReply->type == REDIS_REPLY_STRING) {
				std::string tmp;
				tmp.assign(childReply->str, childReply->len);
				uint64_t uid = strtoull(const_cast<char*>(tmp.c_str()), NULL, 0);
				out.push_back(uid);
			}
		}

		return 0;
	}

	/// ��ͷ��ɾ��һ��Ԫ��
	int list_header_pop(const char* key)
	{
		if (!key)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		char buffer[1024] = { 0 };
		snprintf(buffer, sizeof(buffer), "rpop %s", key);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);
		if( !(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str,"OK")==0))
			return -3;

		return 0;
	}

	int list_size(const char* key)
	{
		if (!key)
			return -1;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		char buffer[1024] = { 0 };
		snprintf(buffer, sizeof(buffer), "llen %s", key);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -2;
		}

		autoR.set(r);
		if(r->type != REDIS_REPLY_INTEGER)
			return -3;

		return r->integer;
	}

	int lock(const char* key, const char* val) {
		if (!key || !val)
			return 0;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		char buffer[1024] = { 0 };
		snprintf(buffer, sizeof(buffer), "SETNX %s %s", key, val);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return 0;
		}

		autoR.set(r);
		if(r->type == REDIS_REPLY_INTEGER )
			return r->integer;

		return 0;
	}

	int unlock(const char* key) {
		if (!key)
			return 0;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		char buffer[1024] = { 0 };
		snprintf(buffer, sizeof(buffer), "del %s", key);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return 0;
		}

		autoR.set(r);
		if(r->type == REDIS_REPLY_INTEGER )
			return r->integer;

		return 0;
	}

	int get_all_val(const char* table, std::vector<std::string>& s1) {
		if (!table)
			return 0;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		char buffer[1024] = { 0 };
		snprintf(buffer, sizeof(buffer), "hgetall %s", table);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return -1;
		}

		autoR.set(r);
		if(r->type != REDIS_REPLY_ARRAY )
			return -1;

		for (size_t i = 0; i < r->elements; ++i) {
			std::string name;
			redisReply* childReply = r->element[i];
			if (childReply->type == REDIS_REPLY_STRING) {
				std::string szVal;
				szVal.assign(childReply->str, childReply->len);
				s1.push_back(szVal);
			}
		}

		return 0;
	}

	int incr(const char* key) {
		if (!key)
			return 0;

		int ret = connect();
		if (0 != ret) {
			LOG_ERR("connect redis failed\n");
			return -1;
		}

		char buffer[1024] = { 0 };
		snprintf(buffer, sizeof(buffer), "incr %s", key);

		CAutoRedisReply autoR;
		redisReply* r = (redisReply*)redisCommand(m_redisCtx, buffer);
		if (NULL == r) {
			LOG_ERR("[%s : %d]: call redisCommand error, redis break connection,m_redisCtx: %lx", __FUNCTION__, __LINE__, m_redisCtx);
			m_isConnect = false;
			return 0;
		}

		autoR.set(r);
		if(r->type != REDIS_REPLY_INTEGER )
			return -1;

		return r->integer>0 ? 1 : 0;
	}

	//////////////////////////////////////////////////////////////////
	void clear()
	{
		if (m_redisCtx)
		{
			redisFree(m_redisCtx);
			m_redisCtx = NULL;
		}
	}

private:
	int connect()
	{
		if (m_isConnect)
			return 0;

		clear();

		struct timeval tv;
		tv.tv_sec = m_timeout/1000;
		tv.tv_usec = m_timeout%1000;

		m_redisCtx = redisConnectWithTimeout(m_szIp.c_str(), m_nPort, tv);
		if (NULL == m_redisCtx || m_redisCtx->err) {
			LOG_ERR("[%s : %d]: connect redis server failed, err: %d, errmsg: %s", __FUNCTION__, __LINE__, m_redisCtx->err, m_redisCtx->errstr);
			clear();
			return -2;		
		}

		m_isConnect = true;
		redisSetTimeout(m_redisCtx, tv);

		return 0;
	}


private:
	bool			m_isConnect;
	redisContext*	m_redisCtx;
	std::string		m_szIp;
	int				m_nPort;
	uint32_t		m_timeout;
};

#endif//redis_client_h_

