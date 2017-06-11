<?php
$name_txt = "/home/tester/1984/modules/recognition/src/lee/name.txt";
$target_dir = "images/";
$target_file = $target_dir . basename($_FILES["fichero"]["name"]);
$name = $_FILES["fichero"]["name"];
$uploadOk = 1;
$imageFileType = pathinfo($target_file,PATHINFO_EXTENSION);
//Check if image file is a actual image or fake image
if(isset($_POST["submit"])) {
    $check = getimagesize($_FILES["fichero"]["tmp_name"]);
    if($check !== false) {
        echo "File is an image - " . $check["mime"] . ".";
        $uploadOk = 1;
    } else {
        echo "File is not an image.";
        $uploadOk = 0;
    }
} else{
    echo "No way ... ";
}

$fileBefore = filemtime($name_txt);

// Check if file already exists
/*if (file_exists($target_file)) {
    echo "Sorry, file already exists.";
    $uploadOk = 0;
}*/
// Check file size
if ($_FILES["fichero"]["size"] > 500000) {
    echo "Sorry, your file is too large.";
    $uploadOk = 0;
}
// Allow certain file formats
if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
&& $imageFileType != "gif" ) {
    echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
    $uploadOk = 0;
}
// Check if $uploadOk is set to 0 by an error
if ($uploadOk == 0) {
    echo "Sorry, your file was not uploaded.";
// if everything is ok, try to upload file
} else {
    if (move_uploaded_file($_FILES["fichero"]["tmp_name"], $target_file)) {
        //header("Location: news.php");

        do{
            clearstatcache();
            sleep(3);
            $fileAfter = filemtime($name_txt);
        }while($fileAfter == $fileBefore);

        header("Location: resultado.php?image=$name");

    } else {
        echo "Sorry, there was an error uploading your file.<br><br>". $_FILES["fichero"]["tmp_name"] . " ----> " . $target_file;
    }
}
?>
