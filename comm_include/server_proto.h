#ifndef _SERVER_PROTO_H__
#define _SERVER_PROTO_H__

#include <stdint.h>
#include "../proto/CommDefine.h"
#pragma pack(1)
enum SERVER_PROTO
{
	SERVER_PROTO_BROADCAST = 1000,
	SERVER_PROTO_BROADCAST_ALL = 1001,	
	
	SERVER_PROTO_LOGIN,    //帐号登录,login srv 通知conn srv放行
	SERVER_PROTO_ENTER,    //选择角色进入游戏, game srv 通知conn srv放行
	SERVER_PROTO_SAVE_PLAYER, //保存玩家信息
	SERVER_PROTO_KICK_ROLE_NOTIFY,		//踢人
	SERVER_PROTO_MAIL_INSERT,		//添加邮件
	SERVER_PROTO_MAIL_GET_ATTACH_REQUEST,		//获取邮件附件
	SERVER_PROTO_MAIL_GET_ATTACH_ANSWER,		//获取邮件附件的回复		
	SERVER_PROTO_REGISTER_SERVER_REQUEST,
	SERVER_PROTO_REGISTER_SERVER_RESPONSE,

	SERVER_PROTO_FETCH_ROLE_REQUEST,
	SERVER_PROTO_FETCH_ROLE_RESPONSE,
	SERVER_PROTO_CREATE_ROLE_REQUEST,
	SERVER_PROTO_CREATE_ROLE_RESPONSE,
	SERVER_PROTO_STORE_ROLE_REQUEST,
	SERVER_PROTO_STORE_ROLE_RESPONSE,
	SERVER_PROTO_STORE_RANK_REQUEST,  //保存排行榜  
	SERVER_PROTO_STORE_RANK_RESPONSE,
	SERVER_PROTO_FETCH_RANK_REQUEST,  //获取排行榜   
	SERVER_PROTO_FETCH_RANK_RESPONSE,

	SERVER_PROTO_STORE_RANK_FIGHT_REQUEST,  //保存排行榜战斗信息	 
	SERVER_PROTO_STORE_RANK_FIGHT_RESPONSE,
	SERVER_PROTO_FETCH_RANK_FIGHT_REQUEST,  //获取排行榜战斗信息	 
	SERVER_PROTO_FETCH_RANK_FIGHT_RESPONSE,	
	SERVER_PROTO_FETCH_SPECIAL_RANK_FIGHT_REQUEST,  //获取某场排行榜战斗信息	 
	SERVER_PROTO_FETCH_SPECIAL_RANK_FIGHT_RESPONSE,
	SERVER_PROTO_FETCH_MAX_FIGHTID_REQUEST,  //获取最大战斗ID信息  
	SERVER_PROTO_FETCH_MAX_FIGHTID_RESPONSE,
	SERVER_PROTO_STORE_OFFLINE_MSG_REQUEST ,     //保存离线消息  
	SERVER_PROTO_FETCH_OFFLINE_MSG_REQUEST,     //获取离线消息 


	SERVER_PROTO_FETCH_OFFLINE_MSG_NOTIFY,     //通知离线消息  
	SERVER_PROTO_RANK_INSERT,				  //插入排行成员
	SERVER_PROTO_STATIS_INFO,				  //插入流水统计库
	SERVER_PROTO_COMPETITIVE_INSERT,			// 插入竞技场
	SERVER_PROTO_COMPETITIVE_RANK_UPDATE,	// 竞技场排名更新
	SERVER_PROTO_COMPETITIVE_GET_NUMBER ,	    // 获取竞技场成员
	SERVER_PROTO_GET_PLAYER_INFO_REQUEST,		// 获取成员基础信息请求
	SERVER_PROTO_GET_PLAYER_INFO_ANSWER,		// 获取成员基础信息应答
	SERVER_PROTO_GET_REWARD_DAY_REQUEST,		// 获取竞技场每日奖励请求
	SERVER_PROTO_GET_USER_DETAIL_REQUEST,		// 获取用户详细信息请求


	SERVER_PROTO_GET_USER_DETAIL_ANSWER,		// 获取用户详细信息应答
	SERVER_PROTO_PLAYER_STATE_REQUEST,			// 用户状态请求
	SERVER_PROTO_PLAYER_STATE_ANSWER ,			// 用户状态应答
	SERVER_PROTO_PLAYER_RECV_POWER_REQUEST,		// 用户接受好友赠送的体力请求
	SERVER_PROTO_PLAYER_RECV_POWER_ANSWER,		// 用户接受好友赠送的体力应答
	SERVER_PROTO_KICK_ROLE_REQUEST,				// 获取角色列表踢人请求
	SERVER_PROTO_KICK_ROLE_ANSWER,				// 获取角色列表踢人应答
	SERVER_PROTO_MONEY_USE_REQUEST,				// 金钱消耗请求
	SERVER_PROTO_MONEY_USE_ANSWER,				// 金钱消耗应答
	SERVER_PROTO_GUILD_SKILL_NOTIFY,			// 公会技能通知

	SERVER_PROTO_ANABASIS_AI_REQUEST,				// 获取远征ai成员
	SERVER_PROTO_FIGHT_GET_PLAYER_REQUEST,			// 获取拼战成员
	SERVER_PROTO_GET_RED_GIFT_ID_REQUEST,			// 获取红包id
	SERVER_PROTO_GET_FRIEND_LIST_REQUEST,			// 获取好友成员请求
	SERVER_PROTO_GET_GUILD_LIST_REQUEST,			// 获取公会成员请求
	SERVER_PROTO_GET_GUILD_AND_FRIEND_LIST_ANSWER,	// 获取公会和好友成员应答
	SERVER_PROTO_ADD_RED_GIFT_REQUEST,				// 增加红包积分请求
	SERVER_PROTO_ADD_ITEM_REQUEST,					// 发送物品
	SERVER_PROTO_GUILD_CHAT_MSG_REQUEST,			// 公会聊天请求
	SERVER_PROTO_GUILD_ZHUIZHAI_HIJACK_REQUEST,    //追债打劫请求

	SERVER_PROTO_GUILD_ZHUIZHAI_HIJACK_ANSWER,	   //追债打劫应答
	SERVER_PROTO_ADD_MONEY_REQUEST,			   //加钱
	SERVER_PROTO_ADD_MACHAI_EXP_REQUEST,		   //增加马仔经验
	SERVER_PROTO_SEND_RED_GIFT_REQUEST,			// 发送红包请求
	SERVER_PROTO_SAVA_CHAT_RECORD_REQUEST,		// 保存玩家聊天记录
	SERVER_PROTO_GET_GUILD_CHAT_REQUEST,		// 获取公会聊天消息
	SERVER_PROTO_GET_RAID_REWARD_REQUEST,		// 获取副本奖励请求
	SERVER_PROTO_GET_RAID_REWARD_ANSWER,		// 获取副本奖励应答
	SERVER_PROTO_RENT_RAID_NOTICE_REQUEST,		// 占领关卡通知播放走马灯
	SERVER_PROTO_MACHAI_ZHUIZHAI_AND_HIJACK_NOTIFY,    //马仔追债和打劫次数通知

	SERVER_PROTO_PLAYER_ONLINE_NOTIFY,					// 用户上线通知
	SERVER_PROTO_MACHAI_RANK_INSERT,					// 插入马仔战争力排行,不需要了
	SERVER_PROTO_FRIEND_NEAR_PLAYER_REQUEST,			// 获取角色附近的人
	SERVER_PROTO_RECHARGE_NOTIFY,						// 充值通知给活动服务器
	SERVER_PROTO_MAX_CONNECTION_NOTIFY,					// 最大连接数统计
	SERVER_PROTO_PLAYER_ENTER_REQUEST,				// 用户进入游戏
	SERVER_PROTO_PK_ZHENGBA_BATTLE_FINISH_REQUEST,	// PK争霸赛战斗结果
	SERVER_PROTO_RENAME_ANSWER,						// 取名应答
	SERVER_PROTO_MACHAI_SHENGXINGRI_NOTIFY,       //马仔升星日的通知
	SERVER_PROTO_QUERY_MACHAI_LEVEL_REQUEST,       //查询马仔等级
	
	SERVER_PROTO_QUERY_MACHAI_LEVEL_ANSWER,       // 查询马仔等级的返回
	SERVER_PROTO_PAY_LOGGER_STATIS_INFO,		  // 插入支付流水统计库
	SERVER_PROTO_GET_ACTIVITY_REQUEST,			  // 获取活动信息请求
	SERVER_PROTO_GET_ACTIVITY_ANSWER,			  // 获取活动信息请求
	SERVER_PROTO_ADD_MACHAI_CHIP_NOTIFY,		  // 获得物品通知
	SERVER_PROTO_MACHAI_UPGRADE_STAR_NOTIFY,	  // 马仔升星
	SERVER_PROTO_ITEM_BUY_NOTIFY,				  // 物品购买
	SERVER_PROTO_ADD_BOSS_RAID_REQUEST,			  // 进入BOSS副本
	SERVER_PROTO_LEAVE_BOSS_RAID_REQUEST,		  // 离开boss副本
	SERVER_PROTO_BOSS_RAID_END_READY_REQUEST,	  // boss副本准备完成

	SERVER_PROTO_BOSS_RAID_USE_PROP_REQUEST,	  // 召唤boss消耗道具请求
	SERVER_PROTO_BOSS_RAID_USE_PROP_ANSWER,		  // 召唤boss消耗道具应答
	SERVER_PROTO_THOUSAND_TOWER_NOTIFY,			  // 闯东星排行榜
	SERVER_PROTO_CREATE_BOSS_RAID_REQUEST,		  // 创建boss副本
	SERVER_PROTO_BOSS_RAID_RELIVE_REQUEST,		  // boss副本复活
	SERVER_PROTO_PLAYER_SEND_NOTICE_REQUEST,	  // boss副本走马灯
	SERVER_PROTO_GET_GUILD_REQUEST,				  // 获取公会请求
	SERVER_PROTO_GET_GUILD_ANSWER,				  // 获取公会应答
	SERVER_PROTO_GET_RANK_BASE_INFO,			  // 获取排行信息

	SERVER_PROTO_PLAYER_RANK_WORSHIP_REQUEST,	  // 排行榜膜拜请求
	SERVER_PROTO_ADD_PLAYER_DONATE_REQUEST,	      // 添加公会捐献
	SERVER_PROTO_SEND_GUILD_RANK_REWARD_REQUEST,	      // 发送公会排名奖励
	SERVER_PROTO_ADD_GUILD_COIN_REQUEST,			// 添加公会建设币

	SERVER_PROTO_RENOWN_UPDATE,					// 名望更新
	SERVER_PROTO_GUILD_SELF_BAR_UPDATE,				// 公会奢华度更新
	SERVER_PROTO_GUILD_SELF_BAR_MACHAI_MAINTAIN_REQUEST,	// 公会个人领地马仔维护请求
	SERVER_PROTO_GUILD_SELF_BAR_GIVE_LEVEL_REWARD,		// 发放公会个人领地奢华奖励
	SERVER_PROTO_CLEAR_MACHAI_MAINTAIN_STATE,		// 清除马仔维护状态
	SERVER_PROTO_GUILD_SELF_BAR_TIP_REWARD,		// 公会个人领地小费奖励

	SERVER_PROTO_GUILD_BOSS_FIGHT_REWARD_REQUEST,		// 公会bOSS挑战奖励请求
	SERVER_PROTO_GUILD_BOSS_FIGHT_REWARD_ANSWER,		// 公会bOSS挑战奖励应答

	SERVER_PROTO_ARTIFACT_RANK_INFO,			// 神器排行信息
	SERVER_PROTO_ARTIFACT_LIKE_INIT_REQUEST,			// 神器点赞初始化请求
	SERVER_PROTO_ARTIFACT_LIKE_REQUEST,			// 神器点赞请求
	SERVER_PROTO_ARTIFACT_LIKE_ANSWER,			// 神器点赞应答

	SERVER_PROTO_MAX_PLAYER_LEVEL_REQUEST,			// 获取最大玩家等级请求
	SERVER_PROTO_MAX_PLAYER_LEVEL_ANSWER,			// 获取最大玩家等级应答

	SERVER_PROTO_COMMON_MONEY_USE_REQUEST,				// 通用金钱消耗请求
	SERVER_PROTO_COMMON_MONEY_USE_ANSWER,				// 通用金钱消耗应答

	SERVER_PROTO_GET_USER_INFO = 9033,          // 后台管理端获取用户信息
	SERVER_PROTO_ADD_ITEM_REQUESRT = 9034,		// 后台管理端增加物品
	SERVER_PROTO_RELOAD_CONFIG_REQUEST,			// game srv重读配置
	SERVER_PROTO_RELOAD_ACTIVE_REQUEST,			// active srv重读配置
	SERVER_PROTO_RELOAD_ACTIVE_ANSWER,			// active srv重读配置的回复
	SERVER_PROTO_GET_OFFLINE_RECHARGE_REQUEST,	// 获取离线充值请求
	SERVER_PROTO_OFFLINE_RECHARGE_LIST_REQUEST,	// 获取离线充值列表请求
	SERVER_PROTO_OFFLINE_RECHARGE_LIST_ANSWER,	// 获取离线充值列表应答

	SERVER_PROTO_SERVER_INFO_NOTIFY,				// 告知world server自己的服务器信息，如服务器id
	SERVER_PROTO_CARNIVAL_DRAW_COST_REQUEST,	//全民狂欢抽奖消耗请求
	SERVER_PROTO_CARNIVAL_DRAW_COST_ANSWER,		//全民狂欢抽奖消耗应答
	SERVER_PROTO_CARNIVAL_DRAW_REWARD,			//全民狂欢抽奖奖励
	SERVER_PROTO_CARNIVAL_HAPPY_REWARD_REQUEST,	//全民狂欢狂欢奖励请求
	SERVER_PROTO_CARNIVAL_HAPPY_REWARD_ANSWER,	//全民狂欢狂欢奖励应答


	SERVER_PROTO_TIREN_LIST_NOTIFY,				// 外挂踢人
};


//除了broadcast的所有消息，第一个字段都是PROTO_HEAD, 最后一个字段都是EXTERN_DATA

typedef struct st_proto_head
{
	uint16_t len;		//长度
	uint16_t msg_id;	//消息ID
	uint16_t seq;		//序号
	uint32_t crc;		//crc校验
	char data[0];		//PROTO 内容
} PROTO_HEAD;

typedef struct proto_head_conn_broadcast
{
	uint16_t len;
	uint16_t msg_id;
	uint16_t seq;
	uint16_t num_player_id;
	PROTO_HEAD proto_head;
	uint64_t player_id[0];
} PROTO_HEAD_CONN_BROADCAST;

//server之间外带的数据
typedef struct extern_data   
{
	uint64_t player_id;
	uint32_t open_id;
	uint16_t fd;
	uint16_t port;	
} EXTERN_DATA;

typedef struct proto_role_login
{
	PROTO_HEAD head;
	uint32_t result;
	uint16_t login_seq;
} PROTO_ROLE_LOGIN;

typedef struct proto_save_player_req
{
	PROTO_HEAD head;	
	uint16_t level;
	uint32_t plug;
	uint16_t data_size;
	uint16_t data2_size;
	char     name[50];
	uint32_t again;
	uint8_t data[0];
} PROTO_SAVE_PLAYER_REQ;

typedef struct proto_save_player_resp
{
	PROTO_HEAD head;
	uint32_t again;
	uint32_t result;
} PROTO_SAVE_PLAYER_RESP;

typedef struct proto_role_kick
{
	PROTO_HEAD head;
	uint32_t reason;
} PROTO_ROLE_KICK;

typedef struct proto_role_enter
{
	PROTO_HEAD head;
	uint8_t job;
	char name[MAX_PLAYER_NAME_LEN];
	uint16_t lv;
	uint64_t player_id;
	uint8_t avata_id;
	uint32_t platform;
	uint32_t ad_channel;
	uint32_t plug;
	uint32_t create_time;
	uint32_t logout_time;
	char    open_id[50];
	char    channel[50];
	uint16_t data1_size; //数据库blob最大64K
	uint16_t data2_size;
	uint8_t data[0];
} PROTO_ROLE_ENTER;

typedef struct proto_mail_insert
{
	PROTO_HEAD head;
	uint64_t player_id;
	uint8_t data[0];
} PROTO_MAIL_INSERT;

typedef struct proto_mail_get_attach
{
	PROTO_HEAD head;
	uint64_t player_id;
	uint8_t data[0];
} PROTO_MAIL_GET_ATTACH;

typedef struct proto_rank_insert
{
	PROTO_HEAD head;
	uint8_t data[0];
} PROTO_RANK_INSERT;


typedef struct proto_rank_competitive_update  /// 将playerid1与playerid2的排名对换
{
	PROTO_HEAD head;
	uint64_t playerid_main;	
	uint64_t playerid_ai;
	uint32_t state;				/// 完成状态: 1-战胜; 0-失败
	uint32_t player_ai_online;	/// ai是否在线; 1: 在线;0: 不在线
}PROTO_RANK_COMPETITIVE_UPDATE;

typedef struct proto_get_player_info_request /// 获取用户基础信息 
{
	PROTO_HEAD head;
	uint16_t   msgid;				//消息id
	uint64_t   playerid;				//待获取的playerid，也是要获取数据的玩家
	/// 副本时有效果	
	uint32_t   raidid;				//挑战副本
	/// 马仔劫持有效
	uint32_t machai_id;				//攻击方的马仔id
	uint32_t target_machai_id;			//防守方的马仔id
}PROTO_GET_PLAYER_INFO_REQUEST;

typedef struct proto_get_player_info_answer
{
	PROTO_HEAD head;
	/// 副本时有效果
	uint32_t raidid;          //挑战副本

	uint32_t machai_id;                          //攻击方的马仔id
	uint32_t target_machai_id;                   //防守方的马仔id
	
	/// 用户信息
	uint8_t job;
	char name[MAX_PLAYER_NAME_LEN];
	uint16_t lv;
	uint64_t player_id;
	uint32_t fc;  /// 战斗力
	uint8_t  avata_id;
	uint32_t msgid;
	uint32_t guild_skill_num;
	uint32_t guild_skill_id[50];
	uint32_t guild_skill_lv[50];
	uint16_t data1_size;
	uint16_t data2_size;
	uint8_t data[0];	
} PROTO_GET_PLAYER_INFO_ANSWER;

typedef struct proto_get_user_detail_request /// 获取用户基础信息 
{
	PROTO_HEAD head;
	uint64_t   playerid;		// 角色id
}PROTO_GET_USER_DETAIL_REQUEST;

typedef struct proto_add_player_donate_request
{
	PROTO_HEAD head;
	uint32_t num;
	uint32_t statis_id;
} PROTO_ADD_PLAYER_DONATE_REQUEST;

typedef struct proto_add_guild_coin_request
{
	PROTO_HEAD head;
	uint32_t num;
	uint32_t statis_id;
} PROTO_ADD_GUILD_COIN_REQUEST;

enum PLAYER_STATUS
{
	ONLINE,               //正常在线玩家
	OFFLINE_SAVING,       //下线玩家,保存数据未返回
};

enum StatisCommitType
{
	COMMIT_MYSQL=0x01,	/// 提交到mysql
};


typedef struct proto_statis_info 
{
	PROTO_HEAD head;
	uint32_t  commit_type;	/// 提交类型

	uint32_t  appid;		/// 应用id
	uint32_t  open_id;		/// 用户openid
	uint64_t  player_id;	/// 角色id
	uint32_t  server_id;	/// 服务器id
	uint32_t  timestamp;	/// 时间戳
	
	uint32_t  magic_id;		/// 用于区别不同活动或者功能的统计

	uint32_t  ext_num1;		/// 扩展整形字段1
	uint32_t  ext_num2;		/// 扩展整形字段2
	uint32_t  ext_num3;		/// 扩展整形字段3
	uint32_t  ext_num4;		/// 扩展整形字段4
	uint32_t  ext_num5;		/// 扩展整形字段5
	uint32_t  ext_num6;		/// 扩展整形字段6
	uint32_t  ext_num7;		/// 扩展整形字段7
	uint32_t  ext_num8;		/// 扩展整形字段8
	uint32_t  ext_num9;		/// 扩展整形字段9
	uint32_t  ext_num10;	/// 扩展整形字段10

	int		  len1;			/// 扩展字段字符串的长度
	char      str1[100];	/// 扩展字段字符串
	int		  len2;			/// 扩展字段字符串的长度
	char      str2[100];	/// 扩展字段字符串
}PROTO_STATIS_INFO;


typedef struct _player_state_request {
	PROTO_HEAD head;
	uint64_t   playerid;
	uint32_t   state;			/// 状态
}PLAYER_STATE_REQUEST;

typedef struct _player_state_answer {
	PROTO_HEAD head;
	uint32_t   state;			/// 状态
	uint32_t   friendNum;	
	uint64_t   playerid;
	uint64_t   friendlist[MAX_FRIEND_NUM];
}PLAYER_STATE_ANSWER;

typedef struct _player_recv_power_request {
	PROTO_HEAD head;
	uint64_t   playerid[MAX_FRIEND_NUM];
	uint32_t   power;			/// 体力值
}PLAYER_RECV_POWER_REQUEST;

typedef struct _player_recv_power_answer {
	PROTO_HEAD head;
	uint64_t   playerid[MAX_FRIEND_NUM];
	uint32_t   monthcard;   /// 月卡
	uint32_t   lifecard;	/// 终身卡
}PLAYER_RECV_POWER_ANSWER;

typedef struct _player_money_use_request 
{
	PROTO_HEAD head;
	uint32_t   id;     //统计id
	uint32_t   gold;
	uint32_t   diamond;
//	uint32_t   statis_id;	/// 统计id
}PLAYER_MONEY_USE_REQUEST;

typedef struct _player_money_use_answer  
{
	PROTO_HEAD head;
	uint32_t result;
	uint32_t id;
}PLAYER_MONEY_USE_ANSWER;

typedef struct _player_guild_skill_notify 
{
	PROTO_HEAD head;
//	uint32_t   id;
//	uint32_t   level;
	uint32_t   n_num;
	uint32_t   skill_id[50];
	uint32_t   skill_lv[50];
}PLAYER_GUILD_SKILL_NOTIFY;

typedef struct _player_anabasis_ai_request 
{
	PROTO_HEAD head;
	uint32_t   serial_num;
}PLAYER_ANABASIS_AI_REQUEST;

typedef struct _player_get_red_gift_id_request 
{
	PROTO_HEAD	head;
	char        name[MAX_PLAYER_NAME_LEN+1];
	uint32_t    wrold_num;
	uint32_t	guild_num;
	uint32_t	friend_num;
	uint32_t	score;			/// 红包总积分
	uint32_t	config_id;
	uint32_t    msgid;
	uint32_t    ext_num;
	char        ext1[50];
	char        ext2[50];
	char        ext3[50];
}PLAYER_GET_RED_GIFT_ID_REQUEST;


typedef struct _player_get_guild_and_friend_list_answer 
{
	PROTO_HEAD	head;
	uint64_t    red_gift_id;			/// 红包id
	uint32_t	score;					/// 红包金额
	uint16_t    friend_num;				/// 好友数目
	uint16_t    guild_num;				/// 同公会成员数目
	uint64_t	friend_playerid[200];	/// 好友列表
	uint64_t	guild_playerid[200];	/// 同公会成员数目
	uint32_t	config_id;
	uint32_t    msgid;
	uint32_t    ext_num;
	char		ext1[50];
	char		ext2[50];
	char		ext3[50];
}PLAYER_GET_GUILD_AND_FRIEND_LIST_ANSWER;

typedef struct _player_friend_near_player_request 
{
	PROTO_HEAD	head;
	uint32_t    friend_num;
	uint64_t	friend_playerid[200];	/// 好友列表

}PLAYER_FRIEND_NEAR_PLAYER_REQUEST;


typedef struct _player_add_red_gift_request 
{
	PROTO_HEAD head;
	char       name[MAX_PLAYER_NAME_LEN+1];
	uint32_t   score;
	uint32_t   type;
}PLAYER_ADD_RED_GIFT_REQUEST;



typedef struct _player_add_item_request 
{
	PROTO_HEAD head;
	uint32_t   statis_id;	/// 统计id
	uint32_t   item_count;	/// 物品数目
	uint32_t   item_id[4];	/// 物品id列表
	uint32_t   item_num[4]; /// 物品个数列表
	uint32_t   drop_id;		/// 掉落id
}PLAYER_ADD_ITEM_REQUEST;

typedef struct _player_guild_chat_msg_request
{
	PROTO_HEAD head;
	uint32_t    guild_id;			/// 公会id
	uint64_t	guild_playerid[200];/// 同公会成员数目
	uint32_t    guild_num;			/// 好友数量
	uint32_t	chattype;			/// 聊天类型
	uint32_t    vipLevel;			/// 发送者vip等级
	uint64_t	chattarget;			/// 接收者id
	char		chatmsg[500];		/// 聊天消息
	char        chatname[50];		/// 发送者名字
}PLAYER_GUILD_CHAT_MSG_REQUEST;

//(A攻-B防）*A血>B血*（B攻-A防）
typedef struct _guild_zhuizhai_hijack_request
{
	PROTO_HEAD head;
	uint64_t    player_id;     //攻击方的player id
	uint64_t    target_player_id;     //防守方的player id	
	uint32_t	machai_id;	/// 攻击方的马仔id
	uint32_t    target_machai_id;		/// 防守方的马仔id
} GUILD_ZHUIZHAI_HIJACK_REQUEST;

struct machai_fight_data
{
	uint32_t id;
	uint32_t attack;
	uint32_t defence;
	uint32_t hp;
};

typedef struct _guild_zhuizhai_hijack_answer
{
	PROTO_HEAD head;
	uint8_t result;           //打劫的结果，1表示胜利，0表示失败, 其他表示出错
	uint64_t    player_id;     //攻击方的player id
	uint64_t    target_player_id;     //防守方的player id
	struct machai_fight_data	machai;	/// 攻击方的马仔
	struct machai_fight_data	target_machai;	/// 防守方的马仔
} GUILD_ZHUIZHAI_HIJACK_ANSWER;


typedef struct _player_add_money_request {
	PROTO_HEAD head;
	uint32_t  type;		/// 1: 金币, 2: 钻石
	uint32_t  val;		/// 价钱值
	uint32_t  statisid;	/// 统计来源id
}PLAYER_ADD_MONEY_REQUEST;	

typedef struct _player_add_machai_exp_request{
	PROTO_HEAD head;
	uint32_t machai_num;	/// 数组数量
	uint32_t  ids[16];	/// id列表
	uint32_t  exps[16];	/// 经验值
	uint32_t  statisid;     /// 统计id
}PLAYER_ADD_MACHAI_EXP_REQUEST;

typedef struct _player_sava_chat_record_request {
	PROTO_HEAD	head;
	char		chat_message[200];
	char		chat_name[MAX_PLAYER_NAME_LEN + 1];
	uint64_t	chat_target_playerid;
	uint64_t	chat_send_playerid;
	uint32_t	chat_type;
	uint32_t	chat_send_vip_level;
}PLAYER_SAVA_CHAT_RECORD_REQUEST;

typedef struct chat_msg_info {
	uint64_t send_playerid;
	uint32_t vipLeve;
	char     chat_name[50];	/// 发送都名字
	char	 chat_msg[200];	/// 消息内容
}*chat_msg_info_ptr;

/// 获取副本奖励请求
typedef struct _player_get_raid_reward_request {  
	PROTO_HEAD	head;
	uint32_t    score;
	uint32_t    raid;
	uint32_t	cur_hurt;
	uint32_t	rent_hurt;					/// 当前占领副本的伤害
	uint64_t	rent_playerid;				/// 当前占领副本的用户
	uint32_t    rent_player_viplevel;	    /// 当前占领副本的用户的viplevel
	uint32_t    attrid[100];
	uint32_t    attrValue[100];
	char		rent_name[50];				/// 当前占领副本的名称
	uint32_t	ten_second;
	uint32_t	continuous;
	uint32_t	unharmed;
}PLAYER_GET_RAID_REWARD_REQUEST;

/// 获取副本奖励应答
typedef struct _player_get_raid_reward_answer {
	PROTO_HEAD	head;
	uint32_t    raid;
	uint32_t	cur_hurt;
	uint32_t	addglod;
	char        name[50];
}PLAYER_GET_RAID_REWARD_ANSWER;

typedef struct _player_send_red_gift_request {
	PROTO_HEAD	head;
	uint32_t    type;  /// 红包类型
	char        ext1[100];
}PLAYER_SEND_RED_GIFT_REQUEST;

typedef struct _player_rent_raid_notice_request
{
	PROTO_HEAD	head;
	uint32_t    raidid;
	char		prevName[50];
	char        curName[50];
	uint32_t	prevVipLevel;
	uint32_t	curVipLevel;
}PLAYER_RENT_RAID_NOTICE_REQUEST;


typedef struct _player_machai_zhuizhai_and_hijack_notify
{
	PROTO_HEAD	head;
	uint32_t	zhuizhai_count;
	uint32_t	hijack_count;
}PLAYER_MACHAI_ZHUIZHAI_AND_HIJACK_NOTIFY;

typedef struct _recharge_notify
{
	PROTO_HEAD	head;
	uint32_t	count;
} RECHARGE_NOTIFY;

typedef struct _max_connection_notify {
	PROTO_HEAD	head;
	uint32_t	ts;
	uint32_t	count;
}MAX_CONNECTION_NOTIFY;

typedef struct _player_enter_request 
{
	PROTO_HEAD	head;
	uint64_t	player_id;
	uint32_t    platform;
	uint32_t	ad_channel;
	char		open_id[50];
	char        channel[50];
}PLAYER_ENTER_REQUEST ;

typedef struct _pk_zhengba_battle_finish_request 
{
	PROTO_HEAD	head;
	uint64_t	player_id1;
	uint64_t	player_id2;
	uint32_t    state1; /// >0: 胜利; =0淘汰
	uint32_t	state2;	/// >0: 胜利; =0淘汰
}PK_ZHENGBA_BATTLE_FINISH_REQUEST ;

typedef struct _player_rename_db_answer 
{
	PROTO_HEAD	head;
	uint32_t    result;
	char        name[50];
}PLAYER_RENAME_DB_ANSWER ;

typedef struct _machai_shengxingri_notify
{
	PROTO_HEAD	head;
	uint32_t    machai_star_level;  //马仔星级
} MACHAI_SHENGXINGRI_NOTIFY;

typedef struct _query_machai_level_request
{
	PROTO_HEAD	head;
	uint32_t    machai_id;  //马仔id
} QUERY_MACHAI_LEVEL_REQUEST;

typedef struct _query_machai_level_answer
{
	PROTO_HEAD	head;
	uint32_t    machai_id;  //马仔id
	uint32_t    machai_star_level;  //马仔星级
} QUERY_MACHAI_LEVEL_ANSWER;

typedef struct _activity_info
{
//	uint32_t id;		/// 公告id
	uint32_t type;		/// 公告类型
	uint32_t begTime;	/// 开始时间
	uint32_t endTime;	/// 结束时间
	double rate;		/// 倍率
	_activity_info() {
//		id = 0;
		type = 0;
		begTime = 0;
		endTime = 0;
		rate = 0;
	}

	_activity_info(const _activity_info& other) {
//		id = other.id;
		type = other.type;
		begTime = other.begTime;
		endTime = other.endTime;
		rate = other.rate;
	}

	_activity_info& operator = (const _activity_info& other) {
//		id = other.id;
		type = other.type;
		begTime = other.begTime;
		endTime = other.endTime;
		rate = other.rate;

		return *this;
	}
}ACTIVITY_INFO;

typedef struct _xianshifuben_entry
{
	uint32_t id;
	uint32_t reward;
	uint32_t reward_limit;
} XIANSHIFUBEN_ENTRY;

typedef struct _xianshifuben_info
{
	XIANSHIFUBEN_ENTRY entry[20];
	uint32_t begTime;	/// 开始时间
	uint32_t endTime;	/// 结束时间
} XIANSHIFUBEN_INFO;

typedef struct _activity_info_answer
{
	PROTO_HEAD	head;	
	uint32_t		sz;				/// 数组大小
	ACTIVITY_INFO	act[100];	/// 活动列表
	XIANSHIFUBEN_INFO xianshifuben_info;
	XIANSHIFUBEN_INFO richang_xianshifuben_info; 	
} ACTIVITY_INFO_ANSWER;

typedef struct _reload_active_answer
{
	PROTO_HEAD	head;	
	uint32_t		result;				/// 数组大小
} RELOAD_ACTIVE_ANSWER;

typedef struct _offline_recharge_request {
	PROTO_HEAD	head;
	uint32_t    num;
	uint64_t    ids[20];
	uint32_t	productids[20];
	uint32_t	moneys[20];
}OFFLINE_RECHARGE_REQUEST;


typedef struct _offline_recharge_answer {
	PROTO_HEAD	head;
	uint32_t    num;
	uint64_t    ids[20];
}OFFLINE_RECHARGE_ANSWER;


typedef struct _player_add_machai_chip_notify
{
	PROTO_HEAD	head;
	uint32_t    sz;				/// 物品数目
	uint32_t	ids[20];		/// id列表
	uint32_t	nums[20];		/// 数目列表
}PLAYER_ADD_MACHAI_CHIP_NOTIFY;

typedef struct _player_machai_upgrade_star_notify
{
	PROTO_HEAD	head;
	uint32_t    quality;				/// 马仔品质
	uint32_t    star;					/// 马仔星级
}PLAYER_MACHAI_UPGRADE_STAR_NOTIFY;

typedef struct _player_item_buy_notify
{
	PROTO_HEAD	head;
	uint32_t    type;			/// 1: 购买体力; 2: 命运币; 3: 金币
	uint32_t	count;			/// 购买次数
	uint32_t	val;			/// 购买数量
}PLAYER_ITEM_BUY_NOTIFY;

typedef struct _player_tiren_list_notify
{
	PROTO_HEAD	head;
	uint32_t	count;			/// 人数
	uint32_t    open_id[50];	/// open_id列表
}PLAYER_TIREN_LIST_NOTIFY;

typedef struct _player_boss_raid_end_ready_request 
{
	PROTO_HEAD	head;
	uint32_t	other_view_count;
	uint32_t	self_view_count;
	uint64_t    other_view_id[20];			/// 我视野中的角色列表
	uint32_t    other_view_point_x[20];		/// X坐标
	uint32_t    other_view_point_y[20];		/// Y坐标
	uint32_t    other_view_hp[20];			/// 血量
	uint64_t	self_view_id[20];			/// 我在该列表的视野中
	uint32_t    self_view_hp[20];			/// 血量
	uint32_t	self_hp;
	uint32_t    self_point_x;				/// 自己的坐标X
	uint32_t    self_point_y;				/// 自己的坐标Y
}PLAYER_BOSS_RAID_END_READY_REQUEST;

typedef struct _player_add_boss_raid_request 
{
	PROTO_HEAD	head;
	uint32_t	boss_id;
	uint32_t	boss_type;
}PLAYER_ADD_BOSS_RAID_REQUEST;

typedef struct _player_leave_boss_raid_request 
{
	PROTO_HEAD	head;
	uint32_t	num;
	uint64_t    player_list[20];
}PLAYER_LEAVE_BOSS_RAID_REQUEST;

typedef struct _player_boss_raid_use_prop_request 
{
	PROTO_HEAD	head;
	uint32_t	id;					/// bossid
	uint32_t    rate;				///  召唤倍数
	uint32_t    prop_id;			/// 需要的道具id
	uint32_t    prop_num;			/// 需要的道具数目
}PLAYER_BOSS_RAID_USE_PROP_REQUEST;


typedef struct _player_boss_raid_use_prop_answer 
{
	PROTO_HEAD	head;
	uint32_t    boss_id;			/// 需要的道具id
	uint32_t    rate;				/// 召唤倍数
}PLAYER_BOSS_RAID_USE_PROP_ANSWER;

typedef struct _player_thousand_tower_notify 
{
	PROTO_HEAD	head;
	uint32_t    score;			/// 本周总积分
	uint32_t    max_serial;		/// 最大序号
}PLAYER_THOUSAND_TOWER_NOTIFY;

typedef struct _player_create_boss_raid_request 
{
	PROTO_HEAD	head;
	uint32_t    bossId;			/// bossid
	uint32_t    bossType;		/// bosstype
	uint32_t    maxhp;			/// 最大血量
}PLAYER_CREATE_BOSS_RAID_REQUEST;

typedef struct _player_boss_raid_relive_request 
{
	PROTO_HEAD	head;
	uint32_t    maxhp;			/// 最大血量
}PLAYER_BOSS_RAID_RELIVE_REQUEST;

typedef struct _player_send_notice_request 
{
	PROTO_HEAD	head;
	char        ext_name1[50];
	char		ext_name2[50];
	char		ext_name3[50];
	char		ext_name4[50];
	char		ext_name5[50];
	uint32_t    id1;			/// 走马灯id1
	uint32_t    id2;			/// 走马灯id2
	uint32_t    id3;			/// 走马灯id3
	uint32_t    ext_id;
	uint32_t    conditionID;	/// 条件id
}PLAYER_SEND_NOTICE_REQUEST;


typedef struct _player_get_guild_answer 
{
	PROTO_HEAD	head;
	uint32_t    guild_id;
}PLAYER_GET_GUILD_ANSWER;

typedef struct _player_get_rank_base_info 
{
	PROTO_HEAD	head;
	uint32_t    num;
	uint32_t    type[20];
	uint32_t    times[20];
}PLAYER_GET_RANK_BASE_INFO;

typedef struct _player_rank_worship_request 
{
	PROTO_HEAD	head;
	uint32_t    type;
	uint32_t    month_card;
	uint32_t    life_card;
}PLAYER_RANK_WORSHIP_REQUEST;

typedef struct _player_renown_update 
{
	PROTO_HEAD	head;
	uint32_t    renown;			/// 名望值
}PLAYER_RENOWN_UPDATE;

typedef struct _player_guild_self_bar_update
{
	PROTO_HEAD	head;
	uint32_t    bar_level;		//奢华等级
	uint32_t	bar_exp;		//奢华度
}PLAYER_GUILD_SELF_BAR_UPDATE;

typedef struct _player_guild_self_bar_machai_maintain_request
{
	PROTO_HEAD	head;
	uint32_t    unit_id;		//部件id
	uint32_t	machai_pos;		//马仔背包位置
	uint32_t	machai_id;		//马仔id
	uint32_t	machai_section;	//马仔段位
}PLAYER_GUILD_SELF_BAR_MACHAI_MAINTAIN_REQUEST;

typedef struct _player_guild_self_bar_give_level_reward
{
	PROTO_HEAD	head;
	uint32_t    reward_id;		//奖励id
	uint32_t	drop_id;		//掉落id
}PLAYER_GUILD_SELF_BAR_GIVE_LEVEL_REWARD;

typedef struct _player_clear_machai_maintain_state
{
	PROTO_HEAD	head;
	uint32_t    pos;		//马仔背包位置
	uint32_t    id;		//马仔id
	uint32_t	section;	//马仔段位
}PLAYER_CLEAR_MACHAI_MAINTAIN_STATE;

typedef struct _player_guild_self_bar_tip_reward
{
	PROTO_HEAD	head;
	uint32_t    customer_id;	//顾客id
	uint32_t	drop_id;		//掉落id
	uint32_t	guild_coin;		//领取的建设币
	uint32_t	guild_donate;	//领取的帮贡
	uint32_t	machai_up_item_ids[4];	//马仔维护提升的道具id
	uint32_t	machai_up_item_rates[4];	//马仔维护提升的道具概率（万分比）
}PLAYER_GUILD_SELF_BAR_TIP_REWARD;

typedef struct _server_info_notify
{
	PROTO_HEAD	head;
	uint32_t    server_id;	//服务器id
} SERVER_INFO_NOTIFY;

typedef struct _player_carnival_draw_request
{
	PROTO_HEAD	head;
	uint32_t    act_id;	//活动id
	uint32_t	type; //抽奖类型
	uint32_t	one_draw_free_used; //一抽已用免费次数
} PLAYER_CARNIVAL_DRAW_REQUEST;

typedef struct _player_carnival_draw_cost_request
{
	PROTO_HEAD	head;
	uint32_t    act_id;	//活动id
	uint32_t	type; //抽奖类型
	uint32_t	diamond_cost; //消耗钻石，为0表示消耗免费次数
} PLAYER_CARNIVAL_DRAW_COST_REQUEST;

typedef struct _player_carnival_draw_cost_answer
{
	PROTO_HEAD	head;
	char		name[64];
	uint32_t	level;
	uint32_t	job;
	uint32_t    act_id;	//活动id
	uint32_t	type; //抽奖类型
	uint32_t	diamond_cost; //消耗钻石，为0表示消耗免费次数
	uint32_t	one_draw_free_used; //一抽已用免费次数
	uint32_t	draw_count; //抽奖次数
} PLAYER_CARNIVAL_DRAW_COST_ANSWER;

typedef struct _player_carnival_draw_reward
{
	PROTO_HEAD	head;
	uint32_t    act_id;	//活动id
	uint32_t	type; //抽奖类型
	uint32_t	diamond_cost; //消耗钻石，为0表示消耗免费次数
	uint32_t	draw_count; //抽奖次数
	uint32_t	earn_diamond; //获得钻石
	uint32_t	happy_val; //获得的狂欢值
	uint32_t	item_id[20]; //奖励道具id
	uint32_t	item_num[20]; //奖励道具num
	uint32_t	red_gift_id[10]; //红包id
	uint32_t	red_gift_item_id[10]; //发红包的道具id
	uint32_t	red_gift_item_num[10]; //发红包的道具数量
	uint32_t	hit_order[10]; //中奖顺序
	uint32_t	hit_level[10]; //中奖档次
	uint32_t	hit_before_diamond[10]; //中奖前钻石
	uint32_t	hit_after_diamond[10]; //中奖后钻石
	uint32_t	hit_diamond[10]; //中奖钻石
} PLAYER_CARNIVAL_DRAW_REWARD;

typedef struct _player_carnival_happy_reward_request
{
	PROTO_HEAD	head;
	uint32_t    act_id;	//活动id
	uint32_t	reward_id; //奖励id
	uint32_t	cur_happpy; //当前狂欢值
} PLAYER_CARNIVAL_HAPPY_REWARD_REQUEST;

typedef struct _player_carnival_happy_reward_answer
{
	PROTO_HEAD	head;
	uint32_t    act_id;	//活动id
	uint32_t	reward_id; //奖励id
	uint32_t	drop_id; //掉落id
} PLAYER_CARNIVAL_HAPPY_REWARD_ANSWER;

typedef struct _player_guild_boss_fight_reward_request
{
	PROTO_HEAD	head;
	uint32_t	boss_map; //boss关卡
	char		guild_name[100]; //帮会名
	uint32_t	player_num; //玩家数量
	uint64_t	players[0]; //玩家id列表
} PLAYER_GUILD_BOSS_FIGHT_REWARD_REQUEST;

typedef struct _player_guild_boss_fight_reward_answer
{
	PROTO_HEAD	head;
	uint32_t	boss_map; //boss关卡
	uint32_t    item_id[40];	//道具id
	uint32_t	item_num[40]; //道具数量
	uint32_t	item_time[40]; //道具时间
} PLAYER_GUILD_BOSS_FIGHT_REWARD_ANSWER;

typedef struct _player_artifact_like_init_request
{
	PROTO_HEAD	head;
	uint32_t	num;
	uint32_t	artifact_id[10]; //神器id
	uint32_t    artifact_ts[10]; //点赞时间
} PLAYER_ARTIFACT_LIKE_INIT_REQUEST;

typedef struct _player_artifact_like_request 
{
	PROTO_HEAD	head;
	uint32_t    artifact_id;
	uint32_t    month_card;
}PLAYER_ARTIFACT_LIKE_REQUEST;

typedef struct _player_online_notify
{
	PROTO_HEAD	head;
	uint32_t	gold;
	uint32_t    diamond;
}PLAYER_ONLINE_NOTIFY;

typedef struct _max_player_level_answer
{
	PROTO_HEAD	head;
	uint32_t	level;
}MAX_PLAYER_LEVEL_ANSWER;

typedef struct _player_common_money_use_request 
{
	PROTO_HEAD head;
	uint32_t   uid;     //唯一id，用于区别操作类型
	uint32_t   oper_id;   //操作id，用于区分操作对象
	uint32_t   gold;
	uint32_t   diamond;
	uint32_t   statis_id;	/// 统计id
}PLAYER_COMMON_MONEY_USE_REQUEST;

typedef struct _player_common_money_use_answer  
{
	PROTO_HEAD head;
	uint32_t uid;     //唯一id，用于区别操作类型
	uint32_t oper_id;   //操作id，用于区分操作对象
	uint32_t result;
}PLAYER_COMMON_MONEY_USE_ANSWER;

#pragma pack() 
#endif

