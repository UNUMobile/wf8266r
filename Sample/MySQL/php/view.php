<?php
    require_once("db_config.php");
    require_once("db.php");

    $db = new DB();
    $db->connect_db($_DB['host'], $_DB['username'], $_DB['password'], $_DB['dbname']);
    $db->query("SELECT * FROM iot");
    while($result = $db->fetch_array())
    {
        //show all data from iot table
        print_r($result);
    }
?>