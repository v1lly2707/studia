<?php

    session_start();

?>

<!doctype html>
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

		<link rel="stylesheet" href="https://code.jquery.com/ui/1.13.2/themes/base/jquery-ui.css">
		



		
	</head>

   	<body>

       
		
	<div id="container">

		<header>
			
			<a href="index.php"><h1>Movies & TV series</h1></a>

			
        </header>

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
            
        <div id="content">

            
            <form action="login_controller.php" method="post">

                <div id="left">

                    Login <br> <input type="text" name="login"> <br>
                    Haslo <br> <input type="password" name="password"> <br><br>
                    <input type="submit" value="Zaloguj sie">
                    <input type="button" value="Nie masz jeszcze konta? Zarejestruj sie" onClick="location.href='register.php';" />
                </div>
            </form>

            <?php

                if(isset($_SESSION['error']))
                {
                    echo $_SESSION['error'];
                    unset($_SESSION['error']);
                }

            ?>
           	
				
				  
        </div>	
					
		
	
	</div>
		

		<footer>

             © 2023 movies&tvseries All Rights Reserved. Filip Świniarski 

        </footer>
	</body>
</html>


    