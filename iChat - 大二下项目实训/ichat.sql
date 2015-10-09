# Host: localhost  (Version: 5.6.11)
# Date: 2015-07-03 23:48:37
# Generator: MySQL-Front 5.3  (Build 4.214)

/*!40101 SET NAMES utf8 */;

#
# Structure for table "cache_add_contact"
#

DROP TABLE IF EXISTS `cache_add_contact`;
CREATE TABLE `cache_add_contact` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `from_user_id` bigint(20) DEFAULT NULL COMMENT '好友申请发送方',
  `to_user_id` bigint(20) DEFAULT NULL COMMENT '好友申请接收方',
  `time` datetime DEFAULT NULL COMMENT '时间',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

#
# Structure for table "cache_user_record"
#

DROP TABLE IF EXISTS `cache_user_record`;
CREATE TABLE `cache_user_record` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` bigint(20) DEFAULT NULL COMMENT '自身账号',
  `contact_id` bigint(20) DEFAULT NULL COMMENT '对方账号',
  `time` timestamp NULL DEFAULT NULL COMMENT '时间',
  `content` text,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='个人消息记录缓存';

#
# Structure for table "contact_relation"
#

DROP TABLE IF EXISTS `contact_relation`;
CREATE TABLE `contact_relation` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` bigint(20) DEFAULT NULL COMMENT '用户账号',
  `contact_id` bigint(20) DEFAULT NULL COMMENT '好友账号',
  `remark` varchar(255) DEFAULT NULL COMMENT '备注名',
  `permission` int(11) DEFAULT NULL COMMENT '权限',
  `class_id` int(11) DEFAULT NULL COMMENT '分组ID',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='好友关系';

#
# Structure for table "group"
#

DROP TABLE IF EXISTS `group`;
CREATE TABLE `group` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `account` bigint(20) DEFAULT NULL COMMENT '群账号',
  `name` varchar(255) DEFAULT NULL COMMENT '群名称',
  `time` timestamp NULL DEFAULT NULL COMMENT '成立时间',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='群';

#
# Structure for table "group_record"
#

DROP TABLE IF EXISTS `group_record`;
CREATE TABLE `group_record` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `group_id` varchar(255) DEFAULT NULL COMMENT '群账号',
  `time` timestamp NULL DEFAULT NULL COMMENT '时间',
  `content` text COMMENT '内容',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='群消息记录';

#
# Structure for table "group_relation"
#

DROP TABLE IF EXISTS `group_relation`;
CREATE TABLE `group_relation` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` bigint(20) DEFAULT NULL COMMENT '用户账号',
  `group_id` bigint(20) DEFAULT NULL COMMENT '群账号',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='群关系';

#
# Structure for table "state_group_record"
#

DROP TABLE IF EXISTS `state_group_record`;
CREATE TABLE `state_group_record` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` bigint(20) DEFAULT NULL COMMENT '用户账号',
  `group_id` bigint(11) DEFAULT NULL COMMENT '群账号',
  `record_id` int(11) DEFAULT NULL COMMENT '当前群已读取到的记录号',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='用户接受群消息状态';

#
# Structure for table "user"
#

DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `account` bigint(20) DEFAULT NULL COMMENT 'chat号',
  `nickname` varchar(255) DEFAULT NULL COMMENT '昵称',
  `head` varchar(255) DEFAULT NULL COMMENT '头像',
  `signature` varchar(255) DEFAULT NULL COMMENT '签名',
  `level` int(11) DEFAULT NULL COMMENT '等级',
  `gender` tinyint(3) DEFAULT NULL COMMENT '性别',
  `age` int(11) DEFAULT NULL COMMENT '年龄',
  `phone` varchar(255) DEFAULT NULL COMMENT '手机号码',
  `hometown` varchar(255) DEFAULT NULL COMMENT '故乡',
  `location` varchar(255) DEFAULT NULL COMMENT '所在地',
  `birth` date DEFAULT NULL COMMENT '生日',
  `password` varchar(255) DEFAULT NULL COMMENT '密码',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8 COMMENT='用户';

#
# Structure for table "user_class"
#

DROP TABLE IF EXISTS `user_class`;
CREATE TABLE `user_class` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL COMMENT '分组名',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='分组';

#
# Structure for table "user_record"
#

DROP TABLE IF EXISTS `user_record`;
CREATE TABLE `user_record` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` bigint(20) DEFAULT NULL COMMENT '自身帐号',
  `contact_id` bigint(20) DEFAULT NULL COMMENT '对方账号',
  `time` timestamp NULL DEFAULT NULL COMMENT '时间',
  `content` text COMMENT '内容',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='个人消息记录';
