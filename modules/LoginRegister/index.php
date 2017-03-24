<?php include 'sessionlogin.php'; loggedCheck(); ?>
<!DOCTYPE html>

<html>
<head>
  <meta charset="UTF-8">
  <title>Login</title>
  <script>
    function validateEmail(email) {
      var re = /^(([^<>()[\]\\.,;:\s@\"]+(\.[^<>()[\]\\.,;:\s@\"]+)*)|(\".+\"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
      return re.test(email);
  }

  function validateName(name){
    var re = /^[a-zA-Z0-9]+$/;
    return re.test(name);
  }

  function validateFormLogin(form) {
    //form = document.getElementById("login-form");
      var pw = form["pw"];
      var email = form["email"];

      if(!validateEmail(email.value)){
        errorMsg("emailValue");
        return false;
      }

      if(pw.value.length < 8 || pw.value.length > 16){
        errorMsg("passwordLength")
        return false;
      }
      return true;
  }

  function validateFormRegister(form) {
      var pw = form["pw"];
      var pw2 = form["pw2"];
      var email = form["email"];
      var name = form["name"];

      if(!validateName(name.value)){
        errorMsg("nameValue");
        return false;
      }

      if(pw.value.length < 8 || pw.value.length > 16){
        errorMsg("passwordLength");
        return false;
      }

      if(pw.value != pw2.value){
        errorMsg("passwordMatch")
        return false;
      }

      if(!validateEmail(email.value)){
        errorMsg("emailValue");
        return false;
      }
  }

  function errorMsg(error) {
    switch(error) {
      case "emailValue":
        document.getElementById("alert").style.display = "block";
        document.getElementById("alertMessage").innerHTML = "Invalid email.";
        break;
      case "passwordLength":
        document.getElementById("alert").style.display = "block";
        document.getElementById("alertMessage").innerHTML = "Password must be between 8 and 16 characters.";
        break;
      case "passwordMatch":
        document.getElementById("alert").style.display = "block";
        document.getElementById("alertMessage").innerHTML = "Password doesn´t match.";
        break;
      case "nameValue":
        document.getElementById("alert").style.display = "block";
        document.getElementById("alertMessage").innerHTML = "Invalid name.";
        break;
      case "login":
        document.getElementById("alert").style.display = "block";
        document.getElementById("alertMessage").innerHTML = "Invalid email or password.";
        break;
      case "register":
        document.getElementById("alert").style.display = "block";
        document.getElementById("alertMessage").innerHTML = "Email already registered.";
        break;
    }
    return false;
  }

  function successMsg(success) {
    switch(success){
      case "register":
        document.getElementById("alert").style.display = "block";
        document.getElementById("alertMessage").innerHTML = "Register successfuly.";
        break;
    }
    return;
  }

  function closeError() {
    document.getElementById("alert").style.display = "none";
  }
  
  </script>
  <link rel="stylesheet" href="css/style.css">
  <link rel="stylesheet" href="css/stylehome.css">
</head>

<body>
  <div class="login-page">
  <div id="alert" class="alert">
    <div class="background"></div>
    <div class="content">
      <div class="text-alert"><span id="alertMessage">Error: default message</span></div>
      <div class="button-alert"><a id="buttonAccept" class="button" onclick="closeError()">Accept</a></div>
    </div>
  </div>
  <div class="form">
    <form class="register-form" method="POST" action="register.php" onsubmit="return validateFormRegister(this)">
      <input type="text" placeholder="name" name="name" id="name"/>
      <input type="password" placeholder="password" name="pw" id="pw"/>
      <input type="password" placeholder="password again" name="pw2" id="pw2"/>
      <input type="text" placeholder="email address" name="email" id="email"/>
      <button>create</button>
      <p class="message">Already registered? <a href="#">Sign In</a></p>
    </form>
    <form id="login-form" class="login-form" method="POST" action="login.php" onsubmit="return validateFormLogin(this)">
      <input type="text" placeholder="email address" name="email" id="email"/>
      <input type="password" placeholder="password" name="pw" id="pw"/>
      <button>login</button>
      <p class="message">Not registered? <a href="#">Create an account</a></p>
    </form>
  </div>
</div>
    <script src='http://cdnjs.cloudflare.com/ajax/libs/jquery/2.1.3/jquery.min.js'></script>
    <script src="js/index.js"></script>
    <script type="text/javascript">
      errorMsg("<?php echo $_GET['error'] ?>");
      successMsg("<?php echo $_GET['success'] ?>");
    </script>
</body>
</html>
