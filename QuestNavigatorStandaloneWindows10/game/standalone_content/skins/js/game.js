/* Функции скина для игры */

// Колбэки

function qspSkinOnInitApi() {
	/* Работаем с подсвеченной версией элемента. Добавляет только правила для оформления рамок элемента картинками.  */
	$('body').borderImage({
		thisElSelector: '.pressed .np-action-outer',
		bgOnly: true,
		transparent: false,
		fullImage: 'skins/gfx/action-selected-303x50.png',
		bottomImage: 'skins/gfx/action-selected-vert-slice-bottom-43x15.png',
		topImage: 'skins/gfx/action-selected-vert-slice-top-43x13.png',
		rightImage: 'skins/gfx/action-selected-horz-slice-right-131x24.png',
		leftImage: 'skins/gfx/action-selected-horz-slice-left-131x24.png',
		centerImage: 'skins/gfx/action-selected-center-slice-43x24.png'
	});
	
	skinTopObjs = parseInt($('#qsp-wrapper-objs').css('top'), 10);
	skinTopUser1 = parseInt($('#qsp-user1').css('top'), 10);
	skinTopUser2 = parseInt($('#qsp-user2').css('top'), 10);

	skinHideInvCaptions();

	qspActsListItemFormat = "<div class='np-action-outer'><div class='np-action-inner'>%TEXT%</div></div>";
    qspObjsListItemFormat = "<img src='%IMAGE%-39x38.png'>";
    qspObjsListSelItemFormat = "<img src='%IMAGE%_active-39x38.png'>";
}

function qspSkinOnDeviceSet() {
	// Вызывается, когда мы узнали, на каком устройстве запущена игра
	var more_games_link = 'http://qsp.su';
	if (qspIsAndroid) {
		more_games_link = 'market://search?q=pub:Butterfly+Lantern';
	} else if (qspIsIos) {
		more_games_link = 'itms-apps://itunes.apple.com/ru/artist/butterfly-lantern-interactive/id508671395';
	}
	$("#more-games-button a").attr('href', more_games_link);
}

function qspSkinOnSetGroupedContent() {
	/* Обычная обработка border-image. Создаются доп. элементы; фон внутри самого элемента прозрачный. 
	применяем эту функцию каждый раз, когда обновлено содержимое окна - могли появиться кнопки */
	$('.np-action-outer').borderImage({
		transparent: false,
		fullImageSizeW: 303,
		fullImageSizeH: 50,
		repeatCenterX: true,
		repeatCenterY: true,
		fullImage: 'skins/gfx/action-303x50.png',
		bottomImage: 'skins/gfx/action-vert-slice-bottom-43x15.png',
		topImage: 'skins/gfx/action-vert-slice-top-43x13.png',
		rightImage: 'skins/gfx/action-horz-slice-right-131x24.png',
		leftImage: 'skins/gfx/action-horz-slice-left-131x24.png',
		centerImage: 'skins/gfx/action-center-slice-43x24.png'
	});
}

function qspSkinOnUpdateSkin() {
	skinSetMusicButton();
	skinSetInvButton();

	skinHideInvCaptions();
	skinHideScrollsOriginal = qspGameSkin.hideScrollAny;
	skinHideScrolls(false);
}

function qspSkinOnFillInvWithObjs() {
	var objCaption = "";
	if ((qspSelectedObjectIndex !== -1) && qspInvObjs) {
		objCaption = qspInvObjs[qspSelectedObjectIndex].desc;
	}
	$('#qsp-user2').html(objCaption);
}

function qspSkinOnSave() {
	skinHideInv();
}

function qspSkinOnLoad() {
	skinHideInv();
}

function qspSkinOnRestart() {
	skinHideInv();
}

// Свои функции

var skinHideScrollsOriginal = 0;
var skinShowInv = false;
var skinMusic = true;
var skinStage = "";
var skinTopObjs = 0;
var skinTopUser1 = 0;
var skinTopUser2 = 0;

function skinSetSoldiersCounter(soldiers) {
	$('#qsp-user1').html(soldiers);
}

function skinToggleMusic() {
	skinMusic = !skinMusic;
	skinSetMusicButton();
	QspLib.setMute(!skinMusic);
}

function skinHideInvCaptions() {
	var show = false;
	if (qspGameSkin !== null) {
		show = qspGameSkin.showObjs;
	}
	if (show) {
		$('#qsp-user1').show();
		$('#qsp-user2').show();
	} else {
		$('#qsp-user1').hide();
		$('#qsp-user2').hide();
	}
}

function skinHideInv() {
	// прячем инвентарь
	if (skinShowInv) {
		skinShowInv = false;
		skinSetInvButton();
		skinMoveInv();
		skinHideScrolls(false);
	}
}

function skinHideScrolls(immediate) {
	qspGameSkin.hideScrollAny = ((skinHideScrollsOriginal === 1) || skinShowInv) ? 1 : 0;
	if (immediate) {
		qspApplyScrollsVisibility();
	}
}

function skinToggleInv() {
	skinShowInv = !skinShowInv;
	skinMoveInv();
	skinSetInvButton();
	skinHideScrolls(true);
}

function skinMoveInv() {
	// Для Андроида просто устанавливаем координаты, для других платформ - делаем анимацию.
	// В Андроиде после анимации предметы инвентаря перестают нажиматься, внутренние глюки браузера, 
	// поэтому приходится делать так.
	if (skinShowInv) {
		if (qspIsAndroid) {
			$('#qsp-wrapper-objs').css('top', '' + (75 + skinTopObjs) + 'px');
			$('#qsp-user1').css('top', '' + (75 + skinTopUser1) + 'px');
			$('#qsp-user2').css('top', '' + (75 + skinTopUser2) + 'px');
			// Без этого странного действия, на Андроиде предметы инвентаря
			// перестают нажиматься после сдвига.
			skinAndroidRefreshBugfix();
		} else {
			$('#qsp-wrapper-objs').transition({ y: '75px' }, 200, 'out');
			$('#qsp-user1').transition({ y: '75px' }, 200, 'out');
			$('#qsp-user2').transition({ y: '75px' }, 200, 'out');
			// Аналогично.
			skinAndroidRefreshBugfix();
		}
	} else {
		if (qspIsAndroid) {
			$('#qsp-wrapper-objs').css('top', '' + skinTopObjs + 'px');
			$('#qsp-user1').css('top', '' + skinTopUser1 + 'px');
			$('#qsp-user2').css('top', '' + skinTopUser2 + 'px');
		} else {
			$('#qsp-wrapper-objs').transition({ y: '0px' }, 200, 'in');
			$('#qsp-user1').transition({ y: '0px' }, 200, 'in');
			$('#qsp-user2').transition({ y: '0px' }, 200, 'in');
		}
	}
}

function skinSetMusicButton() {
	skinToggleButton('#qsp-user-music img', '(button_music_)(on|off)(_pressed)?', '$1' + (skinMusic ? 'on' : 'off') + '$3');
}

function skinSetInvButton() {
	skinToggleButton('#qsp-user-inv img', '(button_inv)(_active)?(_pressed)?', '$1' + (skinShowInv ? '_active' : '') + '$3');
}

function skinSetStage(cssClass) {
	// Переключаем класс всего body, тем самым задаем разный стиль для разных игровых экранов
	var t = $(document.body);
	if ((skinStage !== '') && (t.hasClass(skinStage))) {
		t.removeClass(skinStage);
	}
	skinStage = cssClass;
	if ((cssClass !== '') && (!t.hasClass(cssClass))) {
		t.addClass(cssClass);
	}
}

function skinToggleButton(selector, pattern, replacement)
{
	var t = $(selector);
    var re = new RegExp(pattern, "g");
    var src = t.attr('src');
    var dataPressed = t.attr('data-pressed');
    if ((typeof (src) != 'undefined') && (typeof (dataPressed) != 'undefined')) {
        var btn1 = src.replace(re, replacement);
        var btn2 = dataPressed.replace(re, replacement);
        t.attr('src', btn1);
        t.attr('data-pressed', btn2);
    }
}

function skinAndroidRefreshBugfix()
{
	// Показываем и сразу скрываем невидимый блок размером с экран.
	// Без этого инвентарь на Андроиде перестаёт ловить нажатия на предметы.
	$('#qsp-android-refresh-bugfix').show();
	$('#qsp-android-refresh-bugfix').hide();
}