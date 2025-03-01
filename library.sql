-- MySQL dump 10.13  Distrib 8.0.41, for Linux (x86_64)
--
-- Host: localhost    Database: db_book
-- ------------------------------------------------------
-- Server version	8.0.41-0ubuntu0.24.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `book`
--

DROP TABLE IF EXISTS `book`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `book` (
  `iNum` int NOT NULL,
  `acName` char(20) NOT NULL,
  `acAuthor` char(20) NOT NULL,
  `acPress` char(20) NOT NULL,
  `iAmout` int NOT NULL,
  PRIMARY KEY (`iNum`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `book`
--

LOCK TABLES `book` WRITE;
/*!40000 ALTER TABLE `book` DISABLE KEYS */;
INSERT INTO `book` VALUES (2,'java','1','1',99),(3,'makesi','章一','上海',100),(12,'lol','腾讯','美',50),(520,'java','yushengjun','西安',345);
/*!40000 ALTER TABLE `book` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `borrow`
--

DROP TABLE IF EXISTS `borrow`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `borrow` (
  `iReaderNum` int NOT NULL,
  `acReaderName` char(18) NOT NULL,
  `acSex` char(18) NOT NULL,
  `iBookiNum` int NOT NULL,
  `acBookName` char(18) NOT NULL,
  `data` char(18) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `borrow`
--

LOCK TABLES `borrow` WRITE;
/*!40000 ALTER TABLE `borrow` DISABLE KEYS */;
INSERT INTO `borrow` VALUES (2,'周字号','男',3,'makesi','2024-5-21'),(2,'周字号','男',3,'makesi','2024-5-20'),(2,'周字号','男',3,'masike','2024-5-21'),(4,'22','22',2,'java','444');
/*!40000 ALTER TABLE `borrow` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `after_insert_borrow` AFTER INSERT ON `borrow` FOR EACH ROW BEGIN
  DECLARE book_amout INT;
  DECLARE reader_amout INT;

  
  SET @new_iBookiNum = NEW.iBookiNum;
  SET @new_iReaderNum = NEW.iReaderNum;

  
  SELECT iAmout INTO book_amout FROM book WHERE iNum = @new_iBookiNum;

  
  SELECT iAmout INTO reader_amout FROM reader WHERE iNum = @new_iReaderNum;

  
  IF book_amout IS NOT NULL THEN
    UPDATE book SET iAmout = book_amout - 1 WHERE iNum = @new_iBookiNum;
  END IF;

  
  IF reader_amout IS NOT NULL THEN
    UPDATE reader SET iAmout = reader_amout - 1 WHERE iNum = @new_iReaderNum;
  END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `reader`
--

DROP TABLE IF EXISTS `reader`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `reader` (
  `iNum` int NOT NULL AUTO_INCREMENT,
  `acName` varchar(20) NOT NULL,
  `acSex` enum('男','女','保密') DEFAULT '保密',
  `iMax` int NOT NULL,
  `iAmout` int NOT NULL,
  PRIMARY KEY (`iNum`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reader`
--

LOCK TABLES `reader` WRITE;
/*!40000 ALTER TABLE `reader` DISABLE KEYS */;
INSERT INTO `reader` VALUES (2,'周字号','男',30,30);
/*!40000 ALTER TABLE `reader` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `return1`
--

DROP TABLE IF EXISTS `return1`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `return1` (
  `iReaderNum` int NOT NULL,
  `acReaderName` char(18) NOT NULL,
  `acSex` char(18) NOT NULL,
  `iBookiNum` int NOT NULL,
  `acBookName` char(18) NOT NULL,
  `data` char(18) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `return1`
--

LOCK TABLES `return1` WRITE;
/*!40000 ALTER TABLE `return1` DISABLE KEYS */;
INSERT INTO `return1` VALUES (2,'周字号','男',3,'masike','2024-5-22'),(2,'周字号','男',3,'masike','2024-5-22');
/*!40000 ALTER TABLE `return1` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `after_insert_return1` AFTER INSERT ON `return1` FOR EACH ROW BEGIN
  DECLARE book_amout INT;
  DECLARE reader_amout INT;

  
  SET @new_iBookiNum = NEW.iBookiNum;
  SET @new_iReaderNum = NEW.iReaderNum;

  
  SELECT iAmout INTO book_amout FROM book WHERE iNum = @new_iBookiNum;

  
  SELECT iAmout INTO reader_amout FROM reader WHERE iNum = @new_iReaderNum;

  
  IF book_amout IS NOT NULL THEN
    UPDATE book SET iAmout = book_amout + 1 WHERE iNum = @new_iBookiNum;
  END IF;

  
  IF reader_amout IS NOT NULL THEN
    UPDATE reader SET iAmout = reader_amout + 1 WHERE iNum = @new_iReaderNum;
  END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-03-01 12:09:35

