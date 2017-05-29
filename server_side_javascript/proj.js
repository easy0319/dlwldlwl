var express = require('express');
var app = express();

//메인 페이지
app.get('/', function (req, res) {
  res.send('homePage');
});

//로그인 페이지
app.get('/login', function (req,res) {
  res.send('loginPage');
});

//회원가입 페이지
app.get('/signId', function (req, res) {
  res.send('signIdPage');
});

//회원정보 페이지
app.get('/userInformation',function (req, res) {
  res.send('userInformationPage');
});

//메뉴 페이지
app.get('/menu',function (req,res) {
  res.send('menuPage');
});

//메뉴-최신글페이지
app.get('/menu/newText',function (req,res) {
  res.send('newTextPage');
});

//포트 접속 체크
app.listen(1337, function () {
  console.log('conneted 1337!');
});
