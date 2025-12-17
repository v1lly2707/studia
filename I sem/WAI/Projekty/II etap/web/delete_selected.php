<?php
session_start();

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $selectedImages = isset($_SESSION['selectedImages']) ? $_SESSION['selectedImages'] : [];

    if (isset($_POST['imagesToDelete'])) {
        $imagesToDelete = $_POST['imagesToDelete'];

        
        foreach ($imagesToDelete as $imageId) {
            unset($selectedImages[$imageId]);
        }

       
        $_SESSION['selectedImages'] = $selectedImages;
    }
}

header("Location: selected_images.php");
exit();
?>
