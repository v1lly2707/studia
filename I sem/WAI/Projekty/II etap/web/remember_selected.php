<?php
session_start();
require '../../vendor/autoload.php';
require_once 'business.php';


if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (isset($_POST['selectedImages']) && is_array($_POST['selectedImages'])) {
        $selectedImages = $_POST['selectedImages'];

        $_SESSION['selectedImages'] = $selectedImages;

        $_SESSION['error'] = 'Wybrano.';
        header('Location: index.php');
        exit();
    } else {
        $_SESSION['error'] = 'Nie wybrano żadnych obrazów do zapamiętania.';
        header('Location: index.php');
        exit();
    }
} else {
    $_SESSION['error'] = 'Blad';
    header('Location: index.php');
    exit();
}
