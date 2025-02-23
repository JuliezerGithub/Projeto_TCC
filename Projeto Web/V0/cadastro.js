// Função para alternar entre as abas
function openTab(tabId) {
    var contents = document.getElementsByClassName('tab-content');
    for (var i = 0; i < contents.length; i++) {
        contents[i].classList.remove('active');
    }
    document.getElementById(tabId).classList.add('active');
}

// Função para cadastrar usuário
async function cadastrarUsuario() {
    const username = document.getElementById('username').value;
    const email = document.getElementById('email').value;
    const password = document.getElementById('password').value;

    try {
        const response = await fetch('http://localhost:3001/cadastrar-usuario', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ username, email, password })
        });

        const result = await response.json();
        alert(result.message);
        limparFormulario();
    } catch (error) {
        alert('Erro ao cadastrar usuário: ' + error.message);
        limparFormulario();
    }    

}

// Função para consultar usuário
async function consultarUsuario() {
    const username = document.getElementById('consultaUsername').value;

    try {
        const response = await fetch(`http://localhost:3001/consultar-usuario?username=${username}`);
        const result = await response.json();
        //document.getElementById('resultadoConsulta').innerText = JSON.stringify(result);

        // Chama a função para gerar a tabela com os dados do resultado
        limparFormulario();
        mostrarResultadoNaTabela(result);
    } catch (error) {
        alert('Erro ao consultar usuário: ' + error.message);
        limparFormulario();
    }
}

// Função para consultar todos os usuários
async function consultarTodosUsuarios() {
    try {
        const response = await fetch('http://localhost:3001/consultar-todos-usuarios');
                
        // Verifique se a resposta está OK
        if (!response.ok) {
            throw new Error('Erro na resposta do servidor: ' + response.statusText);
        }

        // Adicione esta linha para depuração
        const textResponse = await response.text(); // Obtenha a resposta como texto
        console.log(textResponse); // Mostre a resposta no console
        
        // Agora tente converter para JSON
        const result = JSON.parse(textResponse);
        mostrarResultadoNaTabela(result);
    } catch (error) {
        alert('Erro ao consultar todos os usuários: ' + error.message);
    }
}


// Função para mostrar os resultados na tabela (mesma função utilizada anteriormente)
function mostrarResultadoNaTabela(result) {
    const resultadoDiv = document.getElementById('resultadoConsulta');
    
    // Limpa qualquer resultado anterior
    resultadoDiv.innerHTML = '';

    // Cria a tabela e o cabeçalho
    const tabela = document.createElement('table');
    tabela.style.width = '100%';
    tabela.setAttribute('border', '1');
    
    const thead = document.createElement('thead');
    const headerRow = document.createElement('tr');
    const headers = ['Nome de Usuário', 'Email', 'Perfil']; // Adapte os cabeçalhos conforme sua tabela

    headers.forEach(headerText => {
        const th = document.createElement('th');
        th.textContent = headerText;
        headerRow.appendChild(th);
    });
    thead.appendChild(headerRow);
    tabela.appendChild(thead);

    // Cria o corpo da tabela
    const tbody = document.createElement('tbody');
    
    if (result.length === 0) {
        // Se não houver resultados, mostra uma mensagem
        const noResultRow = document.createElement('tr');
        const noResultCell = document.createElement('td');
        noResultCell.colSpan = headers.length; // Faz com que a célula ocupe todas as colunas
        noResultCell.textContent = 'Nenhum usuário encontrado.';
        noResultRow.appendChild(noResultCell);
        tbody.appendChild(noResultRow);
    } else {
        // Adiciona os resultados à tabela
        result.forEach(usuario => {
            const row = document.createElement('tr');
            const tdUsername = document.createElement('td');
            const tdEmail = document.createElement('td');
            const tdPerfil = document.createElement('td');

            tdUsername.textContent = usuario.username;
            tdEmail.textContent = usuario.email;
            tdPerfil.textContent = usuario.perfil; // Supondo que o campo "perfil" existe

            row.appendChild(tdUsername);
            row.appendChild(tdEmail);
            row.appendChild(tdPerfil);
            tbody.appendChild(row);
        });
    }

    tabela.appendChild(tbody);
    resultadoDiv.appendChild(tabela);
}

// Função para mostrar os resultados na tabela
function mostrarResultadoNaTabela(result) {
    const resultadoDiv = document.getElementById('resultadoConsulta');
    
    // Limpa qualquer resultado anterior
    resultadoDiv.innerHTML = '';

    // Cria a tabela e o cabeçalho
    const tabela = document.createElement('table');
    tabela.style.width = '100%'; // Ajusta a largura da tabela
    tabela.setAttribute('border', '1');
    
    const thead = document.createElement('thead');
    const headerRow = document.createElement('tr');
    const headers = ['Nome de Usuário', 'Email', 'Perfil']; // Adicione mais cabeçalhos se necessário

    headers.forEach(headerText => {
        const th = document.createElement('th');
        th.textContent = headerText;
        headerRow.appendChild(th);
    });
    thead.appendChild(headerRow);
    tabela.appendChild(thead);

    // Cria o corpo da tabela
    const tbody = document.createElement('tbody');
    
    if (result.length === 0) {
        // Se não houver resultados, mostra uma mensagem
        const noResultRow = document.createElement('tr');
        const noResultCell = document.createElement('td');
        noResultCell.colSpan = headers.length; // Faz com que a célula ocupe todas as colunas
        noResultCell.textContent = 'Nenhum usuário encontrado.';
        noResultRow.appendChild(noResultCell);
        tbody.appendChild(noResultRow);
    } else {
        // Adiciona os resultados à tabela
        result.forEach(usuario => {
            const row = document.createElement('tr');
            const tdUsername = document.createElement('td');
            const tdEmail = document.createElement('td');
            const tdPerfil = document.createElement('td');

            tdUsername.textContent = usuario.username;
            tdEmail.textContent = usuario.email;
            tdPerfil.textContent = usuario.perfil; // Supondo que o campo "perfil" existe

            row.appendChild(tdUsername);
            row.appendChild(tdEmail);
            row.appendChild(tdPerfil);
            tbody.appendChild(row);
        });
    }

    tabela.appendChild(tbody);
    resultadoDiv.appendChild(tabela);
}
// Função para excluir usuário
async function excluirUsuario() {
    const username = document.getElementById('exclusaoUsername').value;

    try {
        const response = await fetch('http://localhost:3001/excluir-usuario', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ username })
        });

        const result = await response.json();
        alert(result.message);
        limparFormulario();
    } catch (error) {
        alert('Erro ao excluir usuário: ' + error.message);
        limparFormulario();
    }
}

// Função para alterar perfil de usuário
async function alterarPerfil() {
    const username = document.getElementById('perfilUsername').value;
    const novoPerfil = document.getElementById('novoPerfil').value;

    try {
        const response = await fetch('http://localhost:3001/alterar-perfil', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ username, novoPerfil })
        });

        const result = await response.json();
        alert(result.message);
        limparFormulario();
    } catch (error) {
        alert('Erro ao alterar perfil: ' + error.message);
        limparFormulario();
    }
}

// Função Limpar Formulário (Chame a função após o cadastro)
function limparFormulario() {
    document.getElementById('username').value = '';
    document.getElementById('email').value = '';
    document.getElementById('password').value = '';
    document.getElementById('consultaUsername').value = '';
    document.getElementById('exclusaoUsername').value = '';
    document.getElementById('perfilUsername').value = '';

}

function toggleTabContent(index) {
    const tabContents = document.querySelectorAll('.tab-content');
    const arrows = document.querySelectorAll('.tab i');
    const currentContent = tabContents[index];
    const currentArrow = arrows[index];

    // Verifica se o conteúdo atual já está aberto
    if (currentContent.classList.contains('.active')) {
        // Fecha o conteúdo e reseta a flexinha
        currentContent.classList.remove('.active');
        currentArrow.classList.remove('rotate');
    } else {
        // Fecha todos os conteúdos abertos e reseta as flexinhas
        tabContents.forEach((content, idx) => {
            content.classList.remove('.active');
            arrows[idx].classList.remove('rotate'); // Corrigido aqui
        });

        // Abre o conteúdo atual e gira a flexinha
        currentContent.classList.add('.active');
        currentArrow.classList.add('rotate');
    }
}