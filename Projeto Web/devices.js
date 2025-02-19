// Função para cadastrar Dispositivo
async function cadastrarUsuario() {
    const devicename = document.getElementById('devicename').value;
    const id = document.getElementById('id').value;
    const password = document.getElementById('password').value;

    try {
        const response = await fetch('http://localhost:3001/cadastrar-usuario', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ devicename, id, password })
        });

        const result = await response.json();
        alert(result.message);
        limparFormulario();
    } catch (error) {
        alert('Erro ao cadastrar usuário: ' + error.message);
        limparFormulario();
    }    

}

function toggleTabContent(index) {
    const tabContents = document.querySelectorAll('.tab-content');
    const arrows = document.querySelectorAll('.tab i');
    const currentContent = tabContents[index];
    const currentArrow = arrows[index];

    // Verifica se o conteúdo atual já está aberto
    if (currentContent.classList.contains('active')) {
        // Fecha o conteúdo e reseta a flexinha
        currentContent.classList.remove('active');
        currentArrow.classList.remove('rotate');
    } else {
        // Fecha todos os conteúdos abertos e reseta as flexinhas
        tabContents.forEach((content, idx) => {
            content.classList.remove('active');
            arrows[idx].classList.remove('rotate'); // Corrigido aqui
        });

        // Abre o conteúdo atual e gira a flexinha
        currentContent.classList.add('active');
        currentArrow.classList.add('rotate');
    }
}
