/*
*  Bridge:
*           Javascript -> QSP Windows10 Runtime Component
*
*/

var qspLibMode = "WINDOWS10";       // "AIR", "PHONEGAP", "AWESOMIUM" - устанавливаем для того, 
                                   // чтобы api.js мог выполнять различный код в зависимости от платформы


var QspLib = null;

$(function () {
    // При загрузке документа, запускаем приложение.
    //onDocumentReady();
    QspLib = new QspLibWinRT.QspLib();
    //qspInitApi();
});

function onDocumentReady() {
	if (QspLib !== null) {
        throw "onDocumentReady must be called only once!";
	}
    QspLib = new QspLibWinRT.QspLib();
	// Запускаем API.
	qspInitApi();
	// Самодельный диалог alert, 
	// так как в Awesomium стандартные диалоги не работают.
	// Короткий вариант будет работать только после полной инициализации.
	// До этого, вызываем напрямую через QspLib.
	window.alert = function(text) { QspLib.alert(text) };

	qspIsDesktop = true;
	// Сообщаем API, что нам стал известен тип устройства.
	qspSetDevice();
}

function debug(str) {
	$(document.body).append(str);
}

function qspLibOnInitApi() {
	setTimeout( function() { // Delay for Mozilla
		// Запуск игры по завершению инициализации API.
		QspLib.restartGame();
	}, 10);
}
