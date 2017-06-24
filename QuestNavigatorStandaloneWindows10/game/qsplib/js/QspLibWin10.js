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
    QspLib = new QspLibWinRT.QspLib();

    // Привязываем колбеки для вызова яваскрипта из компонента WinRT.
    var uwpJsExecutor = QspLib.getUwpJsExecutor();

    uwpJsExecutor.oncallsetgroupedcontentevent = setGroupedContentCallbackHandler;
    uwpJsExecutor.oncallshowsaveslotsdialogevent = showSaveSlotsDialogCallbackHandler;
    uwpJsExecutor.oncallmsgevent = msgCallbackHandler;
    uwpJsExecutor.oncallerrorevent = errorCallbackHandler;
    uwpJsExecutor.oncallmenuevent = menuCallbackHandler;
    uwpJsExecutor.oncallinputevent = inputCallbackHandler;

    uwpJsExecutor.onshowdebugmessageevent = debugCallbackHandler;

    QspLib.callDebugMessage();

    // Обрабатываем нажатие ссылок с кодом "EXEC:"
    $(document).on('click', 'a', interceptExecLink);


	// Запускаем API.
	qspInitApi();
	// Самодельный диалог alert, 
	// так как в Awesomium стандартные диалоги не работают.
	// Короткий вариант будет работать только после полной инициализации.
	// До этого, вызываем напрямую через QspLib.
    window.alert = function (text) { QspLib.alert(text); };

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

// ***   Колбеки   ***************************************************

function debugCallbackHandler(params) {
    var message = params.target.toString();
    log('debug: ' + message);
}

function setGroupedContentCallbackHandler(groupedContent) {
    var jsGroupedContent = JSON.parse(groupedContent.target.toString());
    qspSetGroupedContent(jsGroupedContent);
}

function showSaveSlotsDialogCallbackHandler(saveSlots) {
    var jsSaveSlots = JSON.parse(saveSlots.target.toString());
    qspShowSaveSlotsDialog(jsSaveSlots);
}

function msgCallbackHandler(text) {
    var jsText = text.target.toString();
    qspMsg(jsText);
}

function errorCallbackHandler(error) {
    var jsError = JSON.parse(error.target.toString());
    qspError(jsError);
}

function menuCallbackHandler(menu) {
    var jsMenu = JSON.parse(menu.target.toString());
    qspMenu(jsMenu);
}

function inputCallbackHandler(text) {
    var jsText = text.target.toString();
    qspInput(jsText);
}

// *******************************************************************

function interceptExecLink(event) {
    var link = $(this).attr('href');
    if (link.toUpperCase().startsWith('EXEC:')) {
        event.preventDefault();
        var code = link.substr(5);
        QspLib.execLink(code);
        return false;
    }
}