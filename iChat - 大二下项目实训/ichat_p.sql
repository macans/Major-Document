CREATE TABLE `user` (
`id` int NULL AUTO_INCREMENT,
`account` bigint NULL,
`nickname` varchar NULL,
`head` varchar NULL,
`signature` varchar NULL,
`level` int NULL,
`gender` int NULL,
`age` int NULL,
`phone` varchar(255) NULL,
`homtown` varchar(255) NULL,
`location` varchar(255) NULL,
`birth` date NULL,
`password` varchar NULL,
PRIMARY KEY (`id`, `account`) 
);

CREATE TABLE `group` (
`id` int NULL,
`account` varchar(255) NULL,
`name` varchar(255) NULL,
PRIMARY KEY (`id`) 
);

CREATE TABLE `contact_relation` (
`id` int NULL,
`user_id` bigint(255) NULL,
`contact` bigint(255) NULL,
`remark` varchar(255) NULL,
`permission` int NULL,
`class_id` int NULL,
PRIMARY KEY (`id`) 
);

CREATE TABLE `user_class` (
`id` int NULL,
`name` varchar(255) NULL,
PRIMARY KEY (`id`) 
);

CREATE TABLE `class_content` (
`id` int NULL,
`class_id` int NULL,
`user_id` int NULL,
PRIMARY KEY (`id`) 
);

CREATE TABLE `group_relation` (
`id` int NULL,
`user_id` bigint NULL,
`group_id` bigint NULL,
PRIMARY KEY (`id`) 
);

CREATE TABLE `user_record` (
`id` int NULL,
`person1` bigint(255) NULL,
`person2` bigint(255) NULL,
`time` timestamp NULL,
`content` text NULL,
PRIMARY KEY (`id`) 
);

CREATE TABLE `cache_user_record` (
`id` int NULL,
`person1` bigint(255) NULL,
`person2` bigint(255) NULL,
`time` datetime NULL,
`content` text NULL,
PRIMARY KEY (`id`) 
);

CREATE TABLE `group_record` (
`id` int NULL,
`gruop_id` int NULL,
`time` datetime NULL,
`content` text NULL,
PRIMARY KEY (`id`) 
);

CREATE TABLE `state_group_record` (
`id` int NULL,
`user_id` bigint NULL,
`record_id` int NULL,
PRIMARY KEY (`id`) 
);


ALTER TABLE `contact_relation` ADD CONSTRAINT `自己` FOREIGN KEY (`user_id`) REFERENCES `user` (`account`);
ALTER TABLE `contact_relation` ADD CONSTRAINT `联系人` FOREIGN KEY (`contact`) REFERENCES `user` (`account`);
ALTER TABLE `class_content` ADD CONSTRAINT `class_id` FOREIGN KEY (`class_id`) REFERENCES `user_class` (`id`);
ALTER TABLE `contact_relation` ADD CONSTRAINT `分组` FOREIGN KEY (`class_id`) REFERENCES `user_class` (`id`);
ALTER TABLE `group_relation` ADD CONSTRAINT `群号` FOREIGN KEY (`group_id`) REFERENCES `group` (`account`);
ALTER TABLE `group_relation` ADD CONSTRAINT `群成员` FOREIGN KEY (`user_id`) REFERENCES `user` (`account`);
ALTER TABLE `user_record` ADD CONSTRAINT `用户1` FOREIGN KEY (`person1`) REFERENCES `user` (`account`);
ALTER TABLE `user_record` ADD CONSTRAINT `用户2` FOREIGN KEY (`person2`) REFERENCES `user` (`account`);
ALTER TABLE `state_group_record` ADD CONSTRAINT `用户号` FOREIGN KEY (`user_id`) REFERENCES `user` (`account`);
ALTER TABLE `state_group_record` ADD CONSTRAINT `记录号` FOREIGN KEY (`record_id`) REFERENCES `group_record` (`id`);

