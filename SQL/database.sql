/*Создание пользователя htuser с паролем SecretPassword для работы с БД glsheduler*/
/*Подключение с localhost т.е. локально с системы где работает БД*/
GRANT ALL PRIVILEGES ON glsheduler.* TO htuser@localhost IDENTIFIED BY 'SecretPassword' WITH GRANT OPTION;
/*Доступ с любого удаленного хоста*/
GRANT ALL PRIVILEGES ON glsheduler.* TO htuser@"%" IDENTIFIED BY 'SecretPassword' WITH GRANT OPTION;
/*Содание базы данных glsheduler*/
CREATE DATABASE glsheduler;


CREATE TABLE `glsheduler`.`users` (
  `user_ID` INT NOT NULL AUTO_INCREMENT,
  `login` VARCHAR(45) NOT NULL,
  `fio` VARCHAR(45) NOT NULL,
  `pass` VARCHAR(45) NOT NULL,
  `userrole` INT NOT NULL DEFAULT 1,
  `isactive` TINYINT NOT NULL DEFAULT 1,
  PRIMARY KEY (`user_ID`))
COMMENT = 'Список пользователей';

CREATE TABLE `glsheduler`.`userrole` (
  `role_ID` INT UNSIGNED NOT NULL DEFAULT 1,
  `rolename` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`role_ID`));

INSERT INTO `glsheduler`.`userrole` (`role_ID`, `rolename`) VALUES ('0', 'Администратор');
INSERT INTO `glsheduler`.`userrole` (`role_ID`, `rolename`) VALUES ('1', 'Пользователь');
INSERT INTO `glsheduler`.`userrole` (`role_ID`, `rolename`) VALUES ('2', 'Просмотр');

CREATE TABLE options (
  option_id INT(11) UNSIGNED NOT NULL,
  value VARCHAR(255) NOT NULL,
  comment VARCHAR(255) DEFAULT NULL,
  PRIMARY KEY (option_id)
)

INSERT INTO options(option_id, value, comment) VALUES(1000, 'true', 'Использовать аутентификацию');
