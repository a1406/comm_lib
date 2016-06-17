#ifndef app_data_statis_h_
#define app_data_statis_h_

#include "server_proto.h"
#include <string.h>


#define GAME_APPID 1005
#define GAME_APP_SECRET  "5e7f30b128c6bcdf04ab5c042154e1d0"
#define GAME_STATIS_APPID "0E1C2B3B7F65CC67A47B03D0FFE70CD9"


enum MAGIC_STATIS_ID
{
	MAGIC_ID_TYPE_BEGIN,
	/// 创建银角色
	MAGIC_ID_TYPE_CREATE_PLAYER,
	/// 登陆统计
	MAGIC_ID_TYPE_LOGIN,
	/// 购买vip
	/// ext_num1购买物品的ID
	/// ext_num2购买物品消耗的人民币
	/// ext_num3购买物品发送的钻石数目
	/// ext_num4购买物品赠送的钻石数目
	MAGIC_ID_TYPE_BUY_VIP,


	/// 商店购买
	/// ext_num1: 购买的物品id
	/// ext_num2: 购买的物品数量
	MAGIC_ID_TYPE_SHOP_BUY,	

	/// 货币消耗
	MAGIC_ID_USE_GOLD, 
	MAGIC_ID_USE_DIAMOND,                  /// ext_num1=MAGIC_ID_USE_DIAMOND, ext_num2=count, ext_num3=msgid
	MAGIC_ID_USE_LIEMING_GOLD,
	MAGIC_ID_USE_DRAGON_SOUL,
	MAGIC_ID_USE_ARENA_GOLD,
	MAGIC_ID_USE_POWER,
	MAGIC_ID_USE_ITEM,

	/// 货币增加
	MAGIC_ID_ADD_GOLD, 
	MAGIC_ID_ADD_DIAMOND,
	MAGIC_ID_ADD_LIEMING_GOLD,
	MAGIC_ID_ADD_DRAGON_SOUL,
	MAGIC_ID_ADD_ARENA_GOLD,
	MAGIC_ID_ADD_EXP,
	MAGIC_ID_ADD_POWER,
	MAGIC_ID_ADD_ITEM,
	MAGIC_ID_ADD_RED_SCORE,			/// 增加红包积分
	MAGIC_ID_USE_RED_SCORE,			/// 使用红包积分

	MAGIC_ID_RECHARGE,				/// 充值
	MAGIC_ID_ANABASIS,				/// 远征
	MAGIC_ID_ADD_TITLE,				/// 增加称号
	MAGIC_ID_FINISH_RAID,			/// 完成副本
	MAGIC_ID_TYPE_LOGOUT,			/// 登出
	MAGIC_ID_ADD_VIP_EXP,			/// 增加vip经验
	MAGIC_ID_ADD_GOLD_DOU,			/// 增加金豆
	MAGIC_ID_USE_GOLD_DOU,			/// 使用金豆
	MAGIC_ID_ADD_VIP_LEVEL,			/// 增加viplevel
	MAGIC_ID_USE_WING_POWER,		/// 使用翅膀体力
		
	MAGIC_ID_ADD_WING_POWER,		/// 增加翅膀体力
	MAGIC_ID_ADD_LEVEL,				/// 升级
	MAGIC_ID_ADD_HAPPLY_VALUE,		/// 增加逛欢值
	MAGIC_ID_USE_HAPPLY_VALUE,		/// 使用逛欢值

	MAGIC_ID_ADD_GUILD_DONATE,		/// 增加公会贡献
	MAGIC_ID_USE_GUILD_DONATE,		/// 使用公会贡献

	MAGIC_ID_ADD_GUILD_COIN,		/// 增加公会建设币
	MAGIC_ID_USE_GUILD_COIN,		/// 使用公会建设币

	MAGIC_ID_ADD_PLAYER_DONATE,		/// 增加公会个人贡献
	MAGIC_ID_USE_PLAYER_DONATE,		/// 使用公会个人贡献

	MAGIC_ID_ADD_ITEM_TEMP,			/// 增加道具到临时背包
	MAGIC_ID_CARNIVAL_DRAW_HIT,		/// 全民狂欢抽奖中奖  //vip、类型、花费、顺序、档次、中的、中前、中后

	MAGIC_ID_TYPE_END	
};

enum MAGIC_STATIS_TYPE
{
	/// 使用货币类
	MAGIC_TYPE_BUY_VIP_GIFT = 0x1,		/// 购买vip等级礼包
	MAGIC_TYPE_GET_VIP_GIFT,			/// 领取vip礼包
	MAGIC_TYPE_EQUIP_UPGRADE,			/// 装备升星
	MAGIC_TYPE_EQUIP_STRENGTHEN,		/// 装备强化
	MAGIC_TYPE_RAID_RELIVE,				/// 副本死心复活
	MAGIC_TYPE_MINGGE_LOCKBUY,			/// 猎命师锁定
	MAGIC_TYPE_WING_UPGRADE_STAR,		/// 翅膀升级
	MAGIC_TYPE_PROP_BUY,				/// 道具购买
	MAGIC_TYPE_SHOP_REFRESH,			/// 商店刷新
	MAGIC_TYPE_SHOP_BUY,				/// 商店购买
	MAGIC_TYPE_TEN_ACTIVITY,			/// 十连抽
	MAGIC_TYPE_CLICK_GOLD,				/// 点金手
	MAGIC_TYPE_CLICK_LIEMING,			/// 命运手
	MAGIC_TYPE_GUILD_USE_GOLD,			/// 公会扣钱
	MAGIC_TYPE_RAID_ACT_RESET,			/// 活动副本重置
	MAGIC_TYPE_RAID_ELITE_RESET,		/// 精英副本重置
	MAGIC_TYPE_RAID_ARENA_RESET,		/// 竞技场副本重置
	MAGIC_TYPE_RAID_ANABASIS,			/// 远征副本重置
	MAGIC_TYPE_ITEM_COMPOSE,			/// 物品合成
	MAGIC_TYPE_SKILL_UPGRADE,			/// 技能升级

	/// 增加货币类
	MAGIC_TYPE_MAIL,					/// 邮件
	MAGIC_TYPE_DECOMPOSE_EQUIP,			/// 分解装备
	MAGIC_TYPE_SELL_MINGGE,				/// 出售命格
	MAGIC_TYPE_USE_PROP,				/// 道具兑换
	MAGIC_TYPE_SELL_PROP,				/// 道具出售
	MAGIC_TYPE_DAILY_SIGN,				/// 每日签到请求
	MAGIC_TYPE_ONLINE_REWARD,			/// 连续在线奖励请求
	MAGIC_TYPE_ACHIEVEMENT,				/// 完成成就
	MAGIC_TYPE_DAILY_QUEST,				/// 完成日常任务
	MAGIC_TYPE_FINISH_RAID,				/// 通关副本
	MAGIC_TYPE_LEVEL_GIFT,				/// 等级礼包
	MAGIC_TYPE_RAID_STAR,				/// 副本章节星级奖励
	MAGIC_TYPE_QUEST,					/// 完成主线任务
	MAGIC_TYPE_FINISH_ARENA_RAID,		/// 完成竞技场副本
	MAGIC_TYPE_OPEN_DRAGON_SOUL,		/// 点亮龙魂
	MAGIC_TYPE_VIP_RECHARGE,			/// VIP充值
	MAGIC_TYPE_FRIEND_SEND,				/// 好友赠送
	MAGIC_TYPE_UPGRADE_LEVEL,			/// 升级


	MAGIC_TYPE_MACHAI_INSTALL_EQUIP,	/// 马仔穿戴装备
	MAGIC_TYPE_MACHAI_UNINSTALL_EQUIP,	/// 马仔卸载装备
	MAGIC_TYPE_MACHAI_COMPOSE_EQUIP,	/// 马仔合成装备

	MAGIC_TYPE_EQUIP_COMPOSE,			/// 装备合成
	MAGIC_TYPE_EQUIP_DECOMPOSE,			/// 装备分解

	MAGIC_TYPE_FIGHT_REWARD,			/// 拼战奖励
	MAGIC_TYPE_RUN_GM_CMD,				/// GM命令
	MAGIC_TYPE_GET_RED_GIFT,			/// 领取红包

	MAGIC_TYPE_ZHUIZHAI,				/// 马仔追债
	MAGIC_TYPE_ZHUIZHAI_HIJACK,			/// 马仔追债打劫
	MAGIC_TYPE_RENT_RAID,				/// 占据关卡

	MAGIC_TYPE_FIRST_RECHARGE,			/// 首次充值
	MAGIC_TYPE_CUMULATIVE_RECHARGE,		/// 累计充值
	MAGIC_TYPE_RQUIP_UPGRADE_LEVEL,		/// 装备升级
	MAGIC_TYPE_FRIEND_HELPER,			/// 好友帮助
	MAGIC_TYPE_EQUIP_INHERIT,			/// 装备继承
	MAGIC_TYPE_ANABASIS_PASS,			/// 远征过关
	MAGIC_TYPE_CREATE_GUILD,			/// 创建公会
	MAGIC_TYPE_DONATE_GUILD,			/// 公会捐献
	MAGIC_TYPE_BAICAISHEN_GUILD,		/// 拜财神
	MAGIC_TYPE_ZHUIZHAI_LEVEL_REFRESH,  /// 追债等级刷新
	MAGIC_TYPE_ZHUIZHAI_BUY_COUNT,      //  购买打劫次数
	MAGIC_TYPE_OPEN_GIFT_PACK,			/// 打开礼包
	MAGIC_TYPE_ONLINE_AUTO,				/// 在线自动增长
	MAGIC_TYPE_CDKEY_EXCHANGE,			/// CDKEY兑换

	MAGIC_TYPE_ACTIVE_TIANTIANYOULI,			/// 活动天天有礼
	MAGIC_TYPE_ACTIVE_CAISHENJIADAO,			/// 活动财神驾到
	MAGIC_TYPE_ACTIVE_LEIJICHONGZHI,			/// 活动累积充值
	MAGIC_TYPE_RENAME,						/// 修改名字
	MAGIC_TYPE_UPDATE_VERSION_GIFT,			/// 升级礼包
	MAGIC_TYPE_ACTIVE_MACHAI_SHENGXINGRI,			/// 活动马仔升星日
	MAGIC_TYPE_ACTIVE_DANBICHONGZHI,			/// 活动单笔充值
	MAGIC_TYPE_ACTIVE_VIP_LINGJIANG,			/// 活动vip领奖
	MAGIC_TYPE_ACTIVE_MEIRICHONGZHI,			/// 活动每日充值
	MAGIC_TYPE_MONTH_CARD,					/// 月卡
	MAGIC_TTPE_LIFETIME_CARD,				/// 终生卡
	MAGIC_TYPE_MACHAI_COMPOSE,				/// 合成马仔
	MAGIC_TYPE_MACHAI_UPGRAD_LEVEL,			/// 升级马仔
	MAGIC_TYPE_MACHAI_UPGRAD_STAR,			/// 升星马仔
	MAGIC_TYPE_AUTO_EXPIRE,					/// 自动过期

	MAGIC_TYPE_ACTIVE_HUODESUIPIAN,			/// 活动获得碎片
	MAGIC_TYPE_ACTIVE_MAZAISHENGXING,			/// 活动马仔升星
	MAGIC_TYPE_ACTIVE_TILIGOUMAI,			/// 活动体力购买
	MAGIC_TYPE_ACTIVE_JINBIGOUMAI,			/// 活动金币购买
	MAGIC_TYPE_ACTIVE_MINGYUNBIGOUMAI,		/// 活动命运币购买
	MAGIC_TYPE_WING_UPGRADE_QUALITY,		/// 翅膀升阶
	MAGIC_TYPE_WING_UPGRADE_EVOLVE,			/// 翅膀进化
	MAGIC_TYPE_WING_ACTIVATION,				/// 翅膀激活
	MAGIC_TYPE_CLICK_DRAGON,				/// 龙纹手
	MAGIC_TYPE_THOUSAND_TOWER_RAND,			/// 闯东星
	MAGIC_TYPE_THOUSAND_TOWER_RAID,			/// 闯东星打副本
	MAGIC_TYPE_THOUSAND_TOWER_SWEEP,		/// 闯东星扫荡
	MAGIC_TYPE_THOUSAND_TOWER_RANK_REWARD,	/// 闯东星排行奖励
	MAGIC_TYPE_WORLD_BOSS_REWARD,			/// 世界BOSS
	MAGIC_TYPE_SUMMON_BOSS,					/// 召唤BOSS
	MAGIC_TYPE_SUMMON_BOSS_REWARD,			/// 召唤BOSS奖励

	MAGIC_TYPE_AI_ZHUANZHUAN,               /// 爱转转活动
	MAGIC_TYPE_BUY_MACHAI_SLOT,				/// 购买马仔槽位
	MAGIC_TYPE_SELL_MACHAI,					/// 出售马仔
	MAGIC_TYPE_MERGE_MACHAI,				/// 合并马仔
	MAGIC_TYPE_LIEMING,						/// 猎命
	MAGIC_TYPE_MINGGE_MERGE,				/// 命格合并
	MAGIC_TYPE_TEAM_SWEEP,					/// 组队副本扫荡
	MAGIC_TYPE_TEAM_BUY_COUNT,				/// 组队副本购买次数
	MAGIC_TYPE_RANK_GIVE_COMPENSATION,		/// 排行榜打偿
	MAGIC_TYPE_RANK_WORSHIP,				/// 排行榜膜拜

	MAGIC_TYPE_GUILD_SKILL_UPGRADE,			/// 公会技能升级
	MAGIC_TYPE_GUILD_BOXING_UPGRADE,		/// 公会拳馆升级
	MAGIC_TYPE_GUILD_SHOP_BUY,				/// 公会商店购买

	MAGIC_TYPE_BUY_SHIZHUANG,				/// 公会购买时装
	MAGIC_TYPE_UP_STAR_SHIZHUANG,			/// 时装升星
	MAGIC_TYPE_FIRST_ADD_GUILD,				/// 首次加入公会
	MAGIC_TYPE_SELF_BAR_MACHAI_REWARD,				///个人领地马仔维护奖励

	MAGIC_TYPE_RENOWN_REWARD,				/// 名望累积奖励
	MAGIC_TYPE_PET_BOSS_KILL,				/// 击杀宠物贩子奖励
	MAGIC_TYPE_PET_BOSS_HARM_REWARD,		/// 宠物贩子伤害奖励

	MAGIC_TYPE_GUILD_SELF_BAR_LEVEL_REWARD,	/// 公会个人领地奢华奖励
	MAGIC_TYPE_GUILD_SELF_BAR_DELEGATE_REWARD,	/// 公会个人领地托管奖励
	MAGIC_TYPE_GUILD_SELF_BAR_UPGRADE_UNIT,	/// 公会个人领地升级部件
	MAGIC_TYPE_GUILD_SELF_BAR_TIP_BASE_REWARD,	/// 公会个人领地小费基础奖励
	MAGIC_TYPE_GUILD_SELF_BAR_TIP_DROP_REWARD,	/// 公会个人领地小费掉落奖励
	MAGIC_TYPE_GUILD_SELF_BAR_HELP_ACCE,	/// 公会个人领地帮助加速

	MAGIC_TYPE_GUILD_UPGRADE,				/// 公会升级

	MAGIC_TYPE_TAKE_OUT_TEMP,				/// 提取临时背包
	MAGIC_TYPE_CARNIVAL_DRAW,				/// 全民狂欢抽奖
	MAGIC_TYPE_CARNIVAL_HAPPY_REWARD,		/// 全民狂欢每日奖励

	MAGIC_TYPE_GUILD_BOSS_REWARD,			/// 帮会Boss伤害奖励
	MAGIC_TYPE_GUILD_BOSS_ENCOURAGE,		/// 帮会Boss鼓舞

	MAGIC_TYPE_PET_ACTIVATRE,				/// 宠物激活
	MAGIC_TYPE_PET_UPGRADE_DEGREE,			/// 宠物升阶
	MAGIC_TYPE_PET_BOSS_REFRESH,			/// 宠物贩子刷新
	MAGIC_TYPE_PET_BOSS_BUY_ACT,			/// 宠物贩子购买行动力

	MAGIC_TYPE_SKIN_ACTIVATRE,				/// 变身激活
	MAGIC_TYPE_SKIN_STAR_UP,				/// 变身升星
	MAGIC_TYPE_SKIN_EQUIP_INTENSIFY,		/// 变身装备强化
	MAGIC_TYPE_SKIN_MATERIAL_COMPOSE,		/// 变身材料合成
	MAGIC_TYPE_SKIN_EFFECT,					/// 变身效果

	MAGIC_TYPE_ARTIFACT_ACTIVATE,			/// 神器激活
	MAGIC_TYPE_ARTIFACT_UPGRADE_STRENGTH,	/// 神器强化
	MAGIC_TYPE_ARTIFACT_UPGRADE_QUALITY,	/// 神器进阶
	MAGIC_TYPE_ARTIFACT_BADGE_ACTIVATE,		/// 神器徽章激活
	MAGIC_TYPE_ARTIFACT_BADGE_LEVELUP,		/// 神器徽章升级
	MAGIC_TYPE_ARTIFACT_LIKE,				/// 神器点赞

	MAGIC_TYPE_DAZHECUXIAO_BUY,				/// 活动打折促销

	MAGIC_TYPE_OFFLINE_RESOURCE_REWARD,		/// 离线资源找回

	MAGIC_TYPE_ACTIVE_LEIJIDENGLU,			/// 活动累计登录

	MAGIC_TYPE_DENGJITEHUI_BUY,				/// 活动等级特惠
	MAGIC_TYPE_KAIFUTEHUI_BUY,				/// 活动开服特惠

};


enum SHOP_TYPE
{
	SHOP_TYPE_MYSTERY,					/// 神秘商店
	SHOP_TYPE_GOLD,						/// 金币商店
	SHOP_TYPE_DIAMOND,					/// 钻石商店
	SHOP_TYPE_ARENA,					/// 竞技场商店
	SHOP_TYPE_VIP,						/// VIP商店
	SHOP_TYPE_GUILD,					/// 公会商店
	SHOP_TYPE_SCORE,					/// 积分商店
	SHOP_TYPE_EQUIP,					/// 装备商店
};

enum RAID_FINISH_TYPE
{
	RAID_TYPE_ONCE,						/// 单次完成
	RAID_TYPE_SWEEP,					/// 扫荡
};


static inline void proto_statis_info__init(proto_statis_info* info, uint32_t commit_type, uint32_t appid, uint32_t open_id, uint64_t player_id
							 , uint32_t server_id, uint32_t  timestamp, uint32_t magic_id, uint32_t ext_num1=0, uint32_t ext_num2=0
							 , uint32_t ext_num3=0, uint32_t ext_num4=0, uint32_t ext_num5=0, uint32_t  ext_num6=0, uint32_t ext_num7=0
							 , uint32_t ext_num8=0, uint32_t ext_num9=0, uint32_t ext_num10=0, int len1=0, char* str1=NULL, int len2=0, char* str2=NULL) {

	info->commit_type = commit_type;
	info->appid = appid;
	info->open_id = open_id;
	info->player_id = player_id;
	info->server_id = server_id;
	info->timestamp = timestamp;
	info->magic_id = magic_id;
	info->ext_num1 = ext_num1;
	info->ext_num2 = ext_num2;
	info->ext_num3 = ext_num3;
	info->ext_num4 = ext_num4;
	info->ext_num5 = ext_num5;
	info->ext_num6 = ext_num6;
	info->ext_num7 = ext_num7;
	info->ext_num8 = ext_num8;
	info->ext_num9 = ext_num9;
	info->ext_num10 = ext_num10;
	info->len1 = len1;
	info->len2 = len2;
	
	if (len1)
		memcpy(&info->str1[0], str1, len1);
	if (len2)
		memcpy(&info->str2[0], str2, len2);
}



#endif//app_data_statis_h_
