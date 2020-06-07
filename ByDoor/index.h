//This is a HTML code for web server. 
//Uses java script and ajax to communicate with clients.
//After establishing a connection with the client this HTML is sent to the client. Function ByDoor handleRoot().

//Using Java Script one second timer is created on client which executes JS myTimer function.
//In this function every second status of system is checked and displayed on webpage. 
//After 20 seconds webpage will be automatically closed by function JS windowClose(). 
//If activation button is pressed on webpage, ByDoor handleActivation() is executrd.
//0.5 seconds relay is active.   



const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>

  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
   
      <style>
          html { 
      font-family: Helvetica; 
      display: inline-block; 
      margin: 0px auto; 
      text-align: center;
      } 
          .button {
      background-color: #195B6A; 
      border: none; 
      color: white; 
      padding: 16px 40px; 
      text-decoration: none; 
      font-size: 30px; 
      margin: 2px; 
      cursor: pointer;
      }
      
     </style>
  </head>
  <body>
  
    <h1>Yard gate</h1>
    <button type="button" class="button" onclick="loadDoc()">Change</button>
    <p id="demo">System ready</p>

    <script>
    var myVar = setInterval(myTimer, 1000); 
    var count = 0;
    function loadDoc() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("demo").innerHTML =
          this.responseText;
        }
      };
      xhttp.open("GET", "activation", true);
      xhttp.send();
    }

    function myTimer() {
      count = count + 1;
      if (count < 20 ){
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("demo").innerHTML =
          this.responseText;
        }
      };
      xhttp.open("GET", "status", true);
      xhttp.send();
      }else {
        clearTimeout(myVar);
        windowClose();
      }
    }
    
    function windowClose() {
    window.open('','_parent','');
    window.close();
    }
    
    </script>
  </body>
</html>


)=====";
