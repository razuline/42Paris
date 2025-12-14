


function save_login()
{
	var e = document.getElementById('input_login');
    var login = e.value.trim();
    localStorage.setItem("g_my_login", login);
    if (login == '')
    {
		e.style.border = "2px solid red";
    }
    else
		window.location = 'level1.html';
}

function start_eval()
{
	var lvl = Math.round(6 + 4*Math.random());
	localStorage.setItem("g_my_eval", JSON.stringify([lvl]));
	window.location = "level"+lvl+".html";
}


function load_login()
{
    var login;
    if (!(login = localStorage.getItem("g_my_login")))
        login = ''; // will means full random during sim.
    return (login);
}


function showTab(nb)
{
	for (let i = 0; i < 2; i++)
	{
		if (i == nb)
		{
			document.getElementById("tab_"+i).style.display = "flex";
			e = document.getElementById("button_"+i);
			e.style.color = "#000000";
			e.style.backgroundColor = "#FFFFFF";
			e.style.fontSize = "120%";
			e.style.borderTopWidth = "4px";
			e.style.marginTop = "0px";
			e.style.boxShadow = "5px 0px 5px gray";
		}
		else
		{
			document.getElementById("tab_"+i).style.display = "none";
			e = document.getElementById("button_"+i);
			e.style.color = "#333333";
			e.style.backgroundColor = "#CCCCCC";
			e.style.fontSize = "100%";
			e.style.borderTopWidth = "0px";
			e.style.marginTop = "4px";
			e.style.boxShadow = "3px 0px 5px gray";
		}
	}
}