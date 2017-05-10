// Место для кода.

document.getElementById('logResult').innerHTML = 'log log';

var helloPlugin = new QspLibWinRT.Hello();

var qspLib = new QspLibWinRT.QspLib();

jQuery(function () {
    $('#logResult').html('document is ready');

    $(document).on('click', '#helloButtonGetMessage', function () {
        HelloButtonGetMessage_Click();
    });

    $(document).on('click', '#helloButtonGetModifiedMessage', function () {
        HelloButtonGetModifiedMessage_Click();
    });

    $(document).on('click', '#Button_Clear', function () {
        ButtonClear_Click();
    });
});

function ButtonClear_Click() {
    document.getElementById('logResult').innerHTML = "";
}

function HelloButtonGetMessage_Click() {
    var message = helloPlugin.getMessage();
    $('#logResult').html(message);
}

function HelloButtonGetModifiedMessage_Click() {
    var message = helloPlugin.getModifiedMessage("Эй, привет!");
    $('#logResult').html(message);
}