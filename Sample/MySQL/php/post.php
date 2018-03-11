<?php
    require_once("db_config.php");
    require_once("db.php");

    //POST DATA
    foreach($_POST as $key => $value){
        $$key = $value;
    }
    //GET DATA
    foreach($_GET as $key => $value){
        $$key = $value;
    }

    $db = new DB();
    $db->connect_db($_DB['host'], $_DB['username'], $_DB['password'], $_DB['dbname']);
  
    $sql = "INSERT INTO iot (field1, field2, field3, field4) VALUES (" . $field1 . ", " . $field2 . ", " . $field3 . ", " . $field4 . ")";
    echo $sql;
    $db->query($sql);
?>