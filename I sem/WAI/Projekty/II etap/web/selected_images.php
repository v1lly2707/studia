<?php
session_start();

require '../../vendor/autoload.php';
require_once 'business.php';

if (!isset($_SESSION['user_id'])) {
    header("Location: selected_images.php");
    exit();
}

$selectedImages = getSelectedImages($_SESSION['user_id']); 

?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>Movies & TV series</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <meta name="description" content="Zapamiętane filmy i seriale" />
    <meta name="keywords" content="film,serial,zapamiętane,movies,TV series, recenzje, wybierz" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <link rel="stylesheet" href="wybierz.css" type="text/css" />
    <link href="https://fonts.googleapis.com/css2?family=Josefin+Sans:wght@300&family=Lato:wght@300&display=swap" rel="stylesheet">
</head>

<body>
    <div id="container">

        <header>
            <a href="index.php">
                <h1>Movies & TV series</h1>
            </a>
        </header>

        <nav class="menu">
            <div class="przycisk">
                <a href="index.php">Powrót</a>
            </div>
        </nav>

        <?php if (count($selectedImages)): ?>
            <div id="thumbnails-container">

            <form id="imageForm" method="post" >
                <?php foreach ($selectedImages as $selectedImage): ?>

                    
                    <div class="product">
                        <p><?= $selectedImage['author'] ?></p>
                        <p><?= $selectedImage['title'] ?></p>
                        <a href="view.php?id=<?= $selectedImage['_id'] ?>">
                            <img src="/images/thumbnail_<?= $selectedImage['fileName'] ?>">
                        </a>

                        <br>
                    </div>
                <?php endforeach; ?>

                </form>
            </div>
        <?php else: ?>
            <p>Brak wybranych zdjęć</p>
        <?php endif; ?>

    </div>
    <?php include 'footer.php'; ?>
</body>

</html>
