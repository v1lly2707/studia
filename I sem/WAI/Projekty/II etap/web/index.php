<?php
session_start();

require '../../vendor/autoload.php';
require_once 'business.php';

$images = pages();

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $_SESSION['selectedImages'] = isset($_POST['selectedImages']) ? $_POST['selectedImages'] : [];

}
?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>Movies & TV series</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <meta name="description" content="Najlepsze filmy i seriale w jednym" />
    <meta name="keywords" content="film,serial,najlepsze,movies,TV series, recenzje, wybierz" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <link rel="stylesheet" href="wybierz.css" type="text/css" />
    <link href="https://fonts.googleapis.com/css2?family=Josefin+Sans:wght@300&family=Lato:wght@300&display=swap" rel="stylesheet">

    <style>
        #thumbnails-container {
            text-align: center;
        }

        .product {
            display: inline-block;
            margin: 10px;
        }

        #thumbnails-container input[type="checkbox"] {
            margin-bottom: 5px;
        }

        .small-button {
            display: block;
            margin-top: 10px;
            font-size: 10px;
            padding: 3px 5px;

            width: 150px;
            height: 100px;
        }
    </style>
</head>

<body>
    <div id="container">

        <header>
            <a href="index.php">
                <h1>Movies & TV series</h1>
            </a>
        </header>

        <?php
        if (isset($_SESSION['error'])) {
            echo $_SESSION['error'];
            unset($_SESSION['error']);
        }
        ?>

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

        <?php if (count($images)): ?>
            <div id="thumbnails-container">
                <form id="imageForm" method="post">
                    <?php foreach ($images as $product): ?>
                        <div class="product">
                            <p><?= $product['author'] ?></p>
                            <p><?= $product['title'] ?></p>
                            <input type="checkbox" name="selectedImages[]" value="<?= $product['_id'] ?>" <?php echo isChecked($product['_id']); ?>>
                            <a href="view.php?id=<?= $product['_id'] ?>">
                                <img src="/images/thumbnail_<?= $product['fileName'] ?>">
                            </a>
                            <br>
                        </div>
                    <?php endforeach; ?>
                    <input class="small-button" type="submit" value="Zapamiętaj wybrane">
                </form>
            </div>
        <?php else: ?>
            <p>Brak zdjęć</p>
        <?php endif; ?>

    </div>
    <?php include 'footer.php'; ?>
</body>

</html>

