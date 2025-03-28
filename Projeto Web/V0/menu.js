
//Seleciona o item clicado
var menuItem = document.querySelectorAll('.item-menu')

function selectLink(){
    menuItem.forEach((item)=>
        item.classList.remove('ativo')
    )
    this.classList.add('ativo')
}

menuItem.forEach((item)=>
    item.addEventListener('click', selectLink)
)

// //Expandir o menu
// var btnExp = document.querySelector('#btn-exp')
// var menuSide = document.querySelector('.menu-lateral')

// btnExp.addEventListener('click', function(){
//     menuSide.classList.toggle('expandir')
// })
document.getElementById('btn-exp').addEventListener('click', function() {
    const menuLateral = document.querySelector('.menu-lateral');
    menuLateral.classList.toggle('col-auto');
});

// Função que redireciona para a página home.html
function goToHome() {
    window.location.href = 'home.html'; // Redireciona para dashboard.html
}

// Captura o clique no link com id 'home-link'
document.getElementById('home-link').addEventListener('click', function(event) {
    event.preventDefault(); // Evita o comportamento padrão do link
    goToHome(); // Chama a função que redireciona
});

// Função que redireciona para a página dashboard.html
function goToDashboard() {
    window.location.href = 'dashboard.html'; // Redireciona para dashboard.html
}

// Captura o clique no link com id 'dashboard-link'
document.getElementById('dashboard-link').addEventListener('click', function(event) {
    event.preventDefault(); // Evita o comportamento padrão do link
    goToDashboard(); // Chama a função que redireciona
});

// Função que redireciona para a página devices.html
function goToDevices() {
    window.location.href = 'devices.html'; // Redireciona para dashboard.html
}

// Captura o clique no link com id 'devices-link'
document.getElementById('devices-link').addEventListener('click', function(event) {
    event.preventDefault(); // Evita o comportamento padrão do link
    goToDevices(); // Chama a função que redireciona
});

// Função que redireciona para a página settings.html
function goToSettings() {
    window.location.href = 'settings.html'; // Redireciona para dashboard.html
}

// Captura o clique no link com id 'settings-link'
document.getElementById('settings-link').addEventListener('click', function(event) {
    event.preventDefault(); // Evita o comportamento padrão do link
    goToSettings(); // Chama a função que redireciona
});
