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
    //console.log('onDocumentReady();');
    //$('#debug').append('onDocumentReady();<br>');
    log('');
    log('onDocumentReady();');
    onDocumentReady();
});

function log(text)
{
    $('#debug').append(text + '<br>');
}

function onDocumentReady() {
	if (QspLib !== null) {
        throw "onDocumentReady must be called only once!";
	}
    log('new QspLibWinRT.QspLib();');
    QspLib = new QspLibWinRT.QspLib();
	// Запускаем API.
    log('qspInitApi();');
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
        log('QspLib.restartGame();');
		QspLib.restartGame();
	}, 10);
}
