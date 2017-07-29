CREATE TABLE IF NOT EXISTS `Tags_to_Songs_mapping` (
	`id`	INTEGER NOT NULL,
	`song_id`	INTEGER NOT NULL,
	`tag_id`	INTEGER NOT NULL,
	PRIMARY KEY(`id`),
	FOREIGN KEY(`song_id`) REFERENCES `Songs`(`id`),
	FOREIGN KEY(`tag_id`) REFERENCES `Tags`(`id`)
);