
function VerificaEstado(){
    var porta2_estado = document.getElementById("porta2_estado").innerHTML;
    var porta2_titulo = document.getElementById("porta2_titulo").innerHTML;
    
    var porta3_estado = document.getElementById("porta3_estado").innerHTML;
    var porta3_titulo = document.getElementById("porta3_titulo").innerHTML;
    
 
    if(porta2_estado === "0"){
        document.getElementById("porta2_botao").innerHTML="<a href='/?l2' class='btn btn-success btn-block btn-lg'><img src='http://www.blocodochapolin.com.br/arduino/rele_internet_2_reles_get/lamp_off.png' witdh='20' height='30'> "+porta2_titulo+"</a>";
    } else {
        document.getElementById("porta2_botao").innerHTML="<a href='/?d2' class='btn btn-danger btn-block btn-lg'><img src='http://www.blocodochapolin.com.br/arduino/rele_internet_2_reles_get/lamp_on.png' witdh='20' height='30'> " +porta2_titulo+"</a>";
    }

    if(porta3_estado === "0"){
        document.getElementById("porta3_botao").innerHTML="<a href='/?l3' class='btn btn-success btn-block btn-lg'><img src='http://www.blocodochapolin.com.br/arduino/rele_internet_2_reles_get/lamp_off.png' witdh='20' height='30'> " +porta3_titulo+"</a>";
    } else {
        document.getElementById("porta3_botao").innerHTML="<a href='/?d3' class='btn btn-danger btn-block btn-lg'><img src='http://www.blocodochapolin.com.br/arduino/rele_internet_2_reles_get/lamp_on.png' witdh='20' height='30'> " +porta3_titulo+"</a>";
    }block
       

}
 