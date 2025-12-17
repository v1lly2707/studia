<?php


require 'functions.php';
function isChecked($productId)
{
    if (isset($_POST['selectedImages']) && in_array($productId, $_POST['selectedImages'])) {
        return 'checked';
    } elseif (isset($_SESSION['selectedImages']) && in_array($productId, $_SESSION['selectedImages'])) {
        return 'checked';
    } else {
        return '';
    }
}




function pages()
{
    $page = 1;
    $pageSize = 3;

    if (isset($_GET['p'])) {
        $page = $_GET['p'];
    }
    $db = get_db();
    $opts = [
        'skip'  => ($page - 1) * $pageSize,
        'limit' => $pageSize,
    ];
    $images = $db->products->find([], $opts)->toArray();
    return $images;
}


function getSelectedImages($userId)
{
    $db = get_db();

    
    if (!$db->selected_images) {
        $db->createCollection('selected_images');
    }

    
    $selectedImages = $db->selected_images->find(['user_id' => $userId])->toArray();

    
    $images = [];
    foreach ($selectedImages as $selectedImage) {
        $image = $db->products->findOne(['_id' => $selectedImage['image_id']]);
        if ($image) {
            $images[] = $image;
        }
    }

    return $images;
}

function add_image($db)
{
    if (
        !empty($_POST['author']) &&
        isset($_POST['title']) &&
        isset($_POST['watermark']) &&
        !empty($_FILES['image']) &&
        0 !== $_FILES['image']['size']
    ) {
        $author = $_POST['author'];
        $title = $_POST['title'];
        $watermark = $_POST['watermark'];
        $image = $_FILES['image'];

        $finfo = finfo_open(FILEINFO_MIME_TYPE);
        $file_name = $image['tmp_name'];
        $mime_type = finfo_file($finfo, $file_name);

        if (
            ($mime_type === 'image/jpeg' || $mime_type === 'image/png') &&
            $image['size'] <= 1000000
        ) {
            $upload_dir = '/var/www/dev/src/web/images/';

            $empty = [];
            $id = $db->products->insertOne($empty)->getInsertedId();

            $path_info = pathinfo($image['name']);
            $ext = $path_info['extension'];

            $object = [
                'author' => $author,
                'title' => $title,
                'watermark' => $watermark,
                'fileName' => $id . '.' . $ext
            ];

            $target = $upload_dir . $id . '.' . $ext;
            $tmp_path = $image['tmp_name'];

            if (move_uploaded_file($tmp_path, $target)) {
               
                $db->products->updateOne(
                    ['_id' => $id],
                    ['$set' => $object]
                );

                
                $imagePath = $upload_dir . $id . '.' . $ext;
                addWatermark($imagePath, $watermark, '00FF00'); 

                
                $thumbnailPath = $upload_dir . 'thumbnail_' . $id . '.' . $ext;
                createThumbnail($imagePath, $thumbnailPath, 200, 125);

               
                header('Location: index.php');
                exit;
            } else {
                echo 'Błąd podczas zapisywania pliku.';
            }
        } else {
            if ($image['size'] > 1000000) {
                echo 'Zbyt duży rozmiar pliku. Maksymalny rozmiar to 1 MB.';
            } elseif (!in_array($mime_type, ['image/jpeg', 'image/png'])) {
                echo 'Nieprawidłowy format pliku. Akceptowane formaty to JPEG i PNG.';
            }
        }
    } else {
        echo 'Uzupełnij wszystkie pola!';
    }
}

function addWatermark($imagePath, $watermarkText, $colorHex)
{
    if (exif_imagetype($imagePath) === IMAGETYPE_JPEG) {
        $image = imagecreatefromjpeg($imagePath);
    } elseif (exif_imagetype($imagePath) === IMAGETYPE_PNG) {
        $image = imagecreatefrompng($imagePath);
    } else {
        echo 'Nieprawidłowy format pliku.';
        return;
    }

    $color = imagecolorallocate($image, hexdec(substr($colorHex, 0, 2)), hexdec(substr($colorHex, 2, 2)), hexdec(substr($colorHex, 4, 2)));

    $fontSize = 60; 
    $textWidth = strlen($watermarkText) * 10; 
    $textHeight = 60;

   
    $x = (imagesx($image) - $textWidth) / 2;
    $y = (imagesy($image) - $textHeight) / 2;

    imagestring($image, $fontSize, $x, $y, $watermarkText, $color);

    if (exif_imagetype($imagePath) === IMAGETYPE_JPEG) {
        imagejpeg($image, $imagePath);
    } elseif (exif_imagetype($imagePath) === IMAGETYPE_PNG) {
        imagepng($image, $imagePath);
    }

    imagedestroy($image);
}

function createThumbnail($sourcePath, $thumbnailPath, $width, $height)
{
    if (exif_imagetype($sourcePath) === IMAGETYPE_JPEG) {
        $sourceImage = imagecreatefromjpeg($sourcePath);
    } elseif (exif_imagetype($sourcePath) === IMAGETYPE_PNG) {
        $sourceImage = imagecreatefrompng($sourcePath);
    } else {
        echo 'Nieprawidłowy format pliku.';
        return;
    }

    $thumbnailImage = imagecreatetruecolor($width, $height);

    imagecopyresized($thumbnailImage, $sourceImage, 0, 0, 0, 0, $width, $height, imagesx($sourceImage), imagesy($sourceImage));

    if (exif_imagetype($sourcePath) === IMAGETYPE_JPEG) {
        imagejpeg($thumbnailImage, $thumbnailPath);
    } elseif (exif_imagetype($sourcePath) === IMAGETYPE_PNG) {
        imagepng($thumbnailImage, $thumbnailPath);
    }

    imagedestroy($sourceImage);
    imagedestroy($thumbnailImage);
}


function login()
{
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        $login = $_POST['login'];
        $password = $_POST['password'];

        if (!empty($login) && !empty($password)) {
            $db = get_db();

            $user = $db->users->findOne(['login' => $login]);

            if ($user) {
               
                if (password_verify($password, $user['password'])) {
                    
                    $_SESSION['error'] = '<span style = "color:red" > Zalogowano!</span>';
                    $_SESSION['user_id'] = $user['_id'];
                    header('Location:index.php');
                    exit;
                } else {
                    $_SESSION['error'] = '<span style = "color:white" > Nieprawidlowe haslo </span>';
                    header('Location: login.php');
                    exit;
                }
            } else {
                $_SESSION['error'] = '<span style = "color:white" > Uzytkownik o podanym loginie nie istnieje </span>';
                header('Location: login.php');
                exit;
            }
        } else {
            $_SESSION['error'] = '<span style = "color:white" > Uzupelnij wszystkie dane </span>';
            header('Location: login.php');
            exit;
        }
    }
}
function register()
{
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        $email = $_POST['email'];
        $login = $_POST['login'];
        $password = $_POST['password'];
        $repeat_password = $_POST['re_password'];

        if (!empty($email) && !empty($login) && !empty($password) && !empty($repeat_password)) {
            if ($password === $repeat_password) {
                $db = get_db();

                $existingUser = $db->users->findOne(['login' => $login]);

                if (!$existingUser)
                {

                
                    $hash = password_hash($password, PASSWORD_DEFAULT);
                    $db->users->insertOne([
                        'email' => $email,
                        'login' => $login,
                        'password' => $hash,

                        
                    ]);
                        
                    header('Location: index.php');
                    exit;
                }
                else
                {
                    echo "Istnieje juz uzytkownik o podanym loginie";
                }
            }
        }
        else
        {
            header('Location:register.php');
            exit;
        }
    }
}


?>