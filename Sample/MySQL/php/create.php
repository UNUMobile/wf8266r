<?php
    require_once("db_config.php");
    require_once("db.php");

    $db = new DB();
    $db->connect_db($_DB['host'], $_DB['username'], $_DB['password'], $_DB['dbname']);
    $query = "CREATE TABLE iot (ID int(11) AUTO_INCREMENT,field1 int NULL,field2 int NULL,field3 int NULL,field4 int NULL,creation_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,PRIMARY KEY  (ID))";

    $db->query($query);

    while($result = $db->fetch_array())
    {
        //show all data from iot table
        print_r($result);
    }
?>