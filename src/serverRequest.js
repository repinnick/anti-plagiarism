document.addEventListener("DOMContentLoaded", function () {
  const sendButton = document.getElementById("send"); // button send
  sendButton.addEventListener("click", function () {
    let payload =
      "name=" + encodeURIComponent(document.getElementById("value").value);

    const request = new XMLHttpRequest();
    request.open("POST", "http://34.106.108.107:8080/cgi-bin/script.cgi", true);

    request.addEventListener("readystatechange", function () {
      console.log(parseInt(request.responseText.replace(/[^\d]/g, "")));
      document.querySelector("#img").style = "background: rgba(0, 0, 0, 0.5)";

      document.querySelector("#result").innerHTML = `${parseInt(
        request.responseText.replace(/[^\d]/g, "")
      )}% <br> unique`;
    });

    request.setRequestHeader(
      "Content-Type",
      "application/x-www-form-urlencoded"
    );
    request.send(payload);
  });
});
