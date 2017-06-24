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
    //log('');
    //log('onDocumentReady();');
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
    //log('new QspLibWinRT.QspLib();');
    QspLib = new QspLibWinRT.QspLib();

    // Привязываем колбеки для вызова яваскрипта из компонента WinRT.
    var uwpJsExecutor = QspLib.getUwpJsExecutor();

    uwpJsExecutor.oncallsetgroupedcontentevent = callSetGroupedContentCallbackHandler;
    uwpJsExecutor.oncallshowsaveslotsdialogevent = callShowSaveSlotsDialogCallbackHandler;

    //uwpJsExecutor.onprimefoundevent = debugCallbackHandler;
    // primeFoundEvent is a user-defined event in nativeObject
    // It passes the results back to this thread as they are produced
    // and the event handler that we define here immediately displays them.
    //uwpJsExecutor.showDebugMessageEvent += debugCallbackHandler;
    //onprimefoundevent
    uwpJsExecutor.onshowdebugmessageevent = debugCallbackHandler;

    QspLib.callDebugMessage();

    //setTimeout(function () {

    // Обрабатываем нажатие ссылок с кодом "EXEC:"
    $(document).on('click', 'a', interceptExecLink);


	// Запускаем API.
    //log('qspInitApi();');
	qspInitApi();
	// Самодельный диалог alert, 
	// так как в Awesomium стандартные диалоги не работают.
	// Короткий вариант будет работать только после полной инициализации.
	// До этого, вызываем напрямую через QspLib.
    window.alert = function (text) { QspLib.alert(text); };

	qspIsDesktop = true;
	// Сообщаем API, что нам стал известен тип устройства.
    qspSetDevice();


    //}, 4000);
}

function debug(str) {
	$(document.body).append(str);
}

function qspLibOnInitApi() {
	setTimeout( function() { // Delay for Mozilla
		// Запуск игры по завершению инициализации API.
        //log('QspLib.restartGame();');
		QspLib.restartGame();
	}, 10);
}

function debugCallbackHandler(params) {
    var message = params.target.toString();
    log('debug: ' + message);
}

function callSetGroupedContentCallbackHandler(groupedContent) {
    var jsGroupedContent = JSON.parse(groupedContent.target.toString());
    qspSetGroupedContent(jsGroupedContent);
}

function callShowSaveSlotsDialogCallbackHandler(saveSlots) {
    var jsSaveSlots = JSON.parse(saveSlots.target.toString());
    qspShowSaveSlotsDialog(jsSaveSlots);
}

function interceptExecLink(event) {
    var link = $(this).attr('href');
    if (link.toUpperCase().startsWith('EXEC:')) {
        event.preventDefault();
        var code = link.substr(5);
        QspLib.execLink(code);
        return false;
    }
}