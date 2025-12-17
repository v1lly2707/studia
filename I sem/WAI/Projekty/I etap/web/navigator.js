const data = document.getElementById('data');
data.classList.remove("magik");

const dialog = document.getElementById('dialog-confirm');
dialog.classList.remove("magik");




function displayCoords() {
    navigator.geolocation.getCurrentPosition((position) => {
        alert("Twoja lokalizacja to:\n" + position.coords.latitude + " " + position.coords.longitude);
        console.log(position.coords.latitude + " " + position.coords.longitude);
    });
}




