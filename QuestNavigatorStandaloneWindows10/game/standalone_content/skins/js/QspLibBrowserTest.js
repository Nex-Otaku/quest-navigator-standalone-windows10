/*
*  Bridge:
*           Javascript -> PhoneGap QSP Plugin
*
*/

var qspLibMode = "BROWSER_TEST";       // "AIR", "PHONEGAP" - устанавливаем для того, 
                                   // чтобы api.js мог выполнять различный код в зависимости от платформы

var testStage = 0;

var QspLib = {
    
    restartGame: function() {
		testChangeStage(0);
    },

    executeAction: function(index) {
		testRunAction(index);
    },
    selectObject: function(index) {
        //return cordova.exec(null, null, "QspLib", "selectObject", [index]);
    },
    loadGame: function() {
		qspShowSaveSlotsDialog(getTestSaveSlots(1));
    },
    
    saveGame: function() {
		qspShowSaveSlotsDialog(getTestSaveSlots(0));
    },
    
    saveSlotSelected: function(index, open) {
        //var mode = open ? 1 : 0;
        //return cordova.exec(null, null, "QspLib", "saveSlotSelected", [index, mode]);
    },

    msgResult: function() {
        //return cordova.exec(null, null, "QspLib", "msgResult", []);
    },
    
    errorResult: function() {
        //return cordova.exec(null, null, "QspLib", "errorResult", []);
    },
    
    userMenuResult: function(index) {
        //return cordova.exec(null, null, "QspLib", "userMenuResult", [index]);
    },
    
    inputResult: function(text) {
        //return cordova.exec(null, null, "QspLib", "inputResult", [text]);
    },

    setMute: function(mute) {
        //return cordova.exec(null, null, "QspLib", "setMute", [mute]);
    }
};


//Функция для предзагрузки картинок (сейчас не используется)
jQuery.preloadImages = function () {
    if (typeof arguments[arguments.length - 1] === 'function') {
        var callback = arguments[arguments.length - 1];
    } else {
        var callback = false;
    }
    if (typeof arguments[0] == 'object') {
        var images = arguments[0];
        var n = images.length;
    } else {
        var images = arguments;
        var n = images.length - 1;
    }
    if (n == 0 && typeof callback == 'function') {
        callback();
        return;
    }
    var not_loaded = n;
    for (var i = 0; i < n; i++) {
    	$(images[i]).imagesLoaded().always(function() {
                                                        if (--not_loaded < 1 && typeof callback == 'function') {
                                                            callback();
                                                        }
                                                        });
    }
}

function getTestMainDesc()
{
	if (testStage===0)
	{
		return ('<div id="qsp-cover-wrapper"><div id="qsp-cover-buttons">' +
				/*'<img src="skins/gfx/top_cover.png"><br>' + */
				'<a onclick="javascript:testChangeStage(2);" class="qsp-skin-button"><img src="skins/gfx/main_menu_start-208x43.png" data-pressed="skins/gfx/main_menu_start_pressed-208x43.png"></a><br>' + 
				'<a onclick="javascript:testChangeStage(1);" class="qsp-skin-button"><img src="skins/gfx/main_menu_about-208x43.png" data-pressed="skins/gfx/main_menu_about_pressed-208x43.png"></a><br>' +
				'<a href="http://qsp.su" class="qsp-skin-button"><img src="skins/gfx/main_menu_moregames-208x43.png" data-pressed="skins/gfx/main_menu_moregames_pressed-208x43.png"></a>' +
				'</div></div>'
				);
	}
	else if (testStage===1)
	{
		return ('<br>' +
		'<center><b>Феи: пропавший зонтик</b></center><br>' +
'<br>' +
'<i>Автор:</i> Ajenta Arrow<br>' +
'<br>' +
'<i>Дизайн, оформление:</i> Александра Гришина "yellowsparrow"<br>' +
'<br>' +
'<i>Музыка:</i><br>' +
'	"Easy Lemon", "Airport Lounge" - Kevin MacLeod (<a href="http://incompetech.com/">incompetech.com</a>)<br>' +
'<br>' +
'<br>' +
'<b>Что это за игра?</b><br>' +
'<br>' +
'Это интерактивная история. Вы будете выбирать различные варианты действий, таким образом управляя сюжетом. Ваша цель - достичь успешной концовки.<br>' +
'<br>' +
'<b>Волшебные зонтики</b><br>' +
'<br>' +
'В любой момент игры вы можете использовать волшебные зонтики. Но как только вы выберете действие, ситуация изменится. Поэтому, сначала проверьте - нельзя ли здесь применить зонтик, и пробуйте применить(нажать на иконку зонтика). Иначе момент может быть упущен.<br>' +
'<br>' +
'<br>' +
'<b>Обращение к игрокам:</b><br>' +
'<br>' +
'Если вы хотите сообщить об ошибке, недоработке, предложить свои идеи, или задать вопрос, обращайтесь по адресу <a href="mailto:butterfly-lantern@text-games.ru">butterfly-lantern@text-games.ru</a>.<br>' +
'<br>' +
'Если же вы просто хотите поделиться впечатлением от игры, пожалуйста, оставьте оценку и комментарий на странице игры в App Store.<br>' +
'<br>' +
'Имейте в виду, что App Store не позволяет разработчикам отвечать на комментарии на странице игры. Для обратной связи используйте вышеуказанный e-mail.<br>'
);
	}
	else if (testStage===2)
	{
		return ('В саду у Энке жили феи - три девочки и один мальчик: Алия, Амалия, Анития и Тенай. У Алии были прозрачные жёлтые крылышки, как и положено фее домашнего уюта, и жила она в щели между крышей дома и потолочными балками.<br>' +
				'<br>' +
				'Однажды Алия возвращалась от подруги Амалии к себе домой и обнаружила, что пропал зонтик. Это был её любимый зонтик - красный в жёлтый горошек. С его помощью она зажигала в саду ночных светлячков. Ночью был дождь, и утром она оставила его сушиться на подоконнике своего жилища, а теперь зонтик исчез. Самое странное, что три других зонтика, которые фея оставила сушиться рядом, остались на месте.<br>' +
				'<br>' +
				'Но кто же мог взять её любимый зонтик? Алия взяла оставшиеся три зонтика, чтобы они уж точно никуда не исчезли, и задумалась - что же теперь делать?<br>'
		);
	}
	else if (testStage===3)
	{
		return ('Алия открыла золотой зонт, её душа снова наполнилась радостью. Голова закружилась ещё больше. Крылья ослабели. Ей стало уже всё равно, что пропал зонтик и что она не сможет зажечь ночные светлячки. Да и что такое светлячки, она уже помнила с трудом. Она опустилась на черепицу крыши и уснула. Наутро она проснулась, но это была уже совсем другая история...<br>' +
				'<br>' +
				'Боюсь, что это конец приключений.<br>' +
				'Попробуйте начать игру сначала.<br>'
		);
	}
	return null;
}

function getTestActs()
{
	if (testStage===1)//об игре
	{
		return [
				{image:'', desc:'Назад'}
				];
	}
	else if (testStage===2)//начало
	{
		return [
				{image:'', desc:'Концовка'},
				{image:'', desc:'А это - описание действия, растянутое на две длинные строки. Оно не должно поместиться в одну строку шириной 600 пикселов.'}
				];
	}
	else if (testStage===3)//концовка
	{
		return [
				{image:'', desc:'Заново'}
				];
	}
	return null;
}

function getTestObjs()
{
	if (testStage===2)//начало
	{
		return [
				{desc:'Гранаты', image:'skins/gfx/grenades'},
				{desc:'Патроны', image:'skins/gfx/ammo'},
				{desc:'Динамит', image:'skins/gfx/dynamite'},
				{desc:'Чертежи', image:'skins/gfx/scheme'},
				{desc:'Неизв. устройство', image:'skins/gfx/device'},
				{desc:'Пулемет', image:'skins/gfx/pulemet'},
				{desc:'Анальгетик', image:'skins/gfx/analgetic'},
				{desc:'Плунжер', image:'skins/gfx/plunjer'}
				];
	} 
	else if (testStage===3)//концовка
	{
		return [];
	}
	return null;
}

function getTestSkin()
{
	var skin = {
					disableScroll:0,
					mainBackImagePath:"",
					sysMenuButtonImagePath:"",
					backColor:"#5A5A5A",
					menuBorder:1,
					menuBorderColor:"#FFF",
					fontColor:"#000",
					linkColor:"#F00",
					fontName:"_sans",
					fontSize:16,
					viewAlwaysShow:1,
					showActs:0,
					mainDescIntegratedActions:1,
					showObjs:0,
					showVars:0,
					mainDescTextFormat:"%TEXT%",
					msgTextFormat:"%TEXT%",
					inputTextFormat:"%TEXT%",
					actsListItemFormat:"<div class='np-action-outer'><div class='np-action-inner'>%TEXT%</div></div>",
					objsListItemFormat:"<img src='%IMAGE%-39x38.png'>",
					objsListSelItemFormat:"<img src='%IMAGE%_active-39x38.png'>",
					contentPath:""
					};
	if (testStage===0)//меню
	{
		skin.showActs = 0;
		skin.showObjs = 0;
	}
	else if (testStage===1)//об игре
	{
		skin.showActs = 1;
		skin.showObjs = 0;
	}
	else if (testStage===2)//начало
	{
		skin.showActs = 1;
		skin.showObjs = 1;
	}
	else if (testStage===3)//концовка
	{
		skin.showActs = 1;
		skin.showObjs = 1;
	}
	return skin;
}

function getTestSaveSlots(mode)
{
	return {
					open:mode,
					slots:[	
							'-empty-',
							'-empty-',
							'3',
							'-empty-',
							'-empty-'
							]
				};
}

function testChangeStage(stage)
{
	//console.log('stage ' + stage);
	testStage = stage;

	testRunNewStage();
	
	var content = {
					main:getTestMainDesc(),
					skin:getTestSkin(),
					acts:getTestActs(),
					objs:getTestObjs()
					}; 
	qspSetGroupedContent(content);
}

function testRunAction(actIndex)
{
	if (testStage === 1)//об игре
	{
		if (actIndex==='0')
		{
			testChangeStage(0);//меню
		}
	}
	else if (testStage === 2)//начало
	{
		if (actIndex==='0')
		{
			testChangeStage(3);//концовка
		}
	}
	else if (testStage === 3)//концовка
	{
		if (actIndex==='0')
		{
			testChangeStage(0);//начало
		}
	}
}

function testRunNewStage()
{
	if (testStage === 0)//обложка
	{
		qspView('');
		skinSetStage('cover');
	}
	else if (testStage === 1)//об игре
	{
		skinSetStage('about');
	}
	else if (testStage === 2)//начало
	{
		skinSetStage('main');
	}
	else if (testStage === 3)//проигрыш
	{
		skinSetStage('main');
		qspView('skins/gfx/death-286x252.png');
	}
}


function onPhoneGapDeviceReady() {
    // Now safe to use the PhoneGap API
	testChangeStage(0);
}
