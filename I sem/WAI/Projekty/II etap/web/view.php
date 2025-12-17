<?php


session_start();


require_once 'functions.php';
use MongoDB\BSON\ObjectID;




$db = get_db();



if (!empty($_REQUEST['id'])) {
    $id = $_REQUEST['id'];
    $product = $db->products->findOne(['_id' => new ObjectID($id)]);

    if ($product == null) {
        http_response_code(404);
        exit;
    }
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $_SESSION['selectedImages'] = isset($_POST['selectedImages']) ? $_POST['selectedImages'] : [];
}
?>
<!DOCTYPE html>
<html>
<head>
		<meta charset="UTF-8">
        <title>Movies & TV series</title>
		<meta name="viewport" content="width=device-width, initial-scale=1.0" >


		<meta name="description" content="Najlepsze filmy i seriale w jednym"/>
		<meta name="keywords" content="film,serial,najlepsze,movies,TV series, recenzje, wybierz"/>
		<meta http-equiv="X-UA-Compatible" content="IE=edge"/>
		<link rel="stylesheet" href="wybierz.css" type="text/css"/>
        <link href="https://fonts.googleapis.com/css2?family=Josefin+Sans:wght@300&family=Lato:wght@300&display=swap" rel="stylesheet">


	</head>
<body>

    <div id="container">
        <header>
            <a href="index.php"><h1>Movies & TV series</h1></a>
        </header>

       

        <p><?= $product['author'] ?></p>

        <p><?= $product['title'] ?> </p>

        <img src="/images/<?= $product['fileName'] ?>">

        <nav class="menu">
            <div class="przycisk">
                <input type="button" value="Dodaj zdjecie" onClick="location.href='form.php';" />
            </div>
            <?php
            if (isset($_SESSION['user_id'])) {
                echo '<div class="przycisk">';
                echo '<a href="logout.php">Wyloguj</a>';
                echo '</div>';
            } else {
                echo '<div class="przycisk">';
                echo '<input type="button" value="Logowanie" onClick="location.href=\'login.php\';" />';
                echo '</div>';
            }
            ?>
        </nav>
    </div>

    <footer>
            
        © 2023 movies&tvseries All Rights Reserved. Filip Świniarski 

    </footer>

</body>
</html>
