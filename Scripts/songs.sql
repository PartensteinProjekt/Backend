CREATE TABLE `Songs` (
	`id`	INTEGER NOT NULL,
	`name`	TEXT NOT NULL,
	`album_id`	INTEGER NOT NULL,
	`file_name`	TEXT NOT NULL,
	`artist_id`	INTEGER NOT NULL,
	`time_in_ms`	INTEGER NOT NULL,
	`plays`	INTEGER NOT NULL DEFAULT 0,
	`grenre_id`	INTEGER NOT NULL,
	`bpm`	INTEGER NOT NULL DEFAULT 0,
	PRIMARY KEY(`id`),
	FOREIGN KEY(`album_id`) REFERENCES `Albums`(`id`),
	FOREIGN KEY(`artist_id`) REFERENCES `Artists`(`id`),
	FOREIGN KEY(`grenre_id`) REFERENCES `Genres`(`id`)
);