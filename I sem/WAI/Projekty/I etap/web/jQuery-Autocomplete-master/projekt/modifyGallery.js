const gallery = document.getElementsByClassName("gallery")[0];
let mode = false;

const node = document.createElement("b");
const textnode = document.createTextNode("(moja osobista opinia)");
node.appendChild(textnode);
document.getElementById("moja").appendChild(node);

const dialog = document.getElementById('polska');
dialog.classList.remove("magik");


function changeStyle()
{
    if(mode)
    {
        mode = false;
        gallery.classList.remove("modifyGallery");
    }
    else
    {
        mode = true;
        gallery.classList.add("modifyGallery");

    }
}