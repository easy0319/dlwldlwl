var express = require('express');
var app = express();
app.set('view engine', 'jade');
app.set('views', './views');
app.use(express.static('public'));  //정적인 파일 추가
app.get('/template', function (req, res) {
  res.render('temp');
});
app.get('/',function (req, res) {
  res.send('Hello home page');
});
app.get('/dynamic',function (req,res) {
  var lis = '';
  for(var i=0;i<5;i++){
    lis += '<li>coding</li>';
  }
  var time =Date();
  var output = `
  <!DOCTYPE html>
  <html>
    <head>
      <meta charset="utf-8">
      <title></title>
    </head>
    <body>
      hello dynamic!
      ${lis}
      ${time}
    </body>
  </html>`;
  res.send(output);
})
app.get('/route',function (req,res) { //정적인 파일
  res.send('hello router, <img src="/a.jpg>"')
})
app.get('/login',function (req, res) {
  res.send('<h1>Login please<h1>');
});
app.listen(3000, function(){
  console.log('conneted 3000 port!');
});
