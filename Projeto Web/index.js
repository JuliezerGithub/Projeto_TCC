const express = require('express');
const { Pool } = require('pg');
const cors = require('cors');
const app = express();
const PORT = process.env.PORT || 3001;  // Alterar para uma porta diferente, como 3001

// Middleware para lidar com JSON e CORS
app.use(express.json());
app.use(cors());

// Configuração da conexão com o PostgreSQL
const pool = new Pool({
    user: 'postgres',   // Substitua com o nome de usuário do PostgreSQL
    host: 'localhost',
    database: 'controle_usuarios',
    password: 'SenhaPostgres@2024!', // Substitua com sua senha do PostgreSQL
    port: 5432,
});

// Rota para cadastrar um usuário
app.post('/cadastrar-usuario', async (req, res) => {
    const { username, email, password } = req.body;
    try {
        await pool.query(
            'INSERT INTO usuarios (username, email, password) VALUES ($1, $2, $3)',
            [username, email, password]
        );
        res.json({ message: 'Usuário cadastrado com sucesso!' });
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

// Rota para consultar todos os usuários
app.get('/consultar-todos-usuarios', async (req, res) => {
    try {
        const result = await pool.query('SELECT * FROM usuarios');
        res.json(result.rows);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

// Rota para consultar usuário
app.get('/consultar-usuario', async (req, res) => {
    const { username } = req.query;
    try {
        const result = await pool.query(
            'SELECT * FROM usuarios WHERE username = $1',
            [username]
        );
        res.json(result.rows);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

// Rota para excluir usuário
app.post('/excluir-usuario', async (req, res) => {
    const { username } = req.body;
    try {
        await pool.query(
            'DELETE FROM usuarios WHERE username = $1',
            [username]
        );
        res.json({ message: 'Usuário excluído com sucesso!' });
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

// Rota para alterar perfil de usuário
app.post('/alterar-perfil', async (req, res) => {
    const { username, novoPerfil } = req.body;
    try {
        await pool.query(
            'UPDATE usuarios SET perfil = $1 WHERE username = $2',
            [novoPerfil, username]
        );
        res.json({ message: 'Perfil alterado com sucesso!' });
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

// Rota para autenticar o usuário
app.post('/login', async (req, res) => {
    const { username, password } = req.body;

    try {
        // Verifica se o usuário existe e se a senha está correta
        const result = await pool.query(
            'SELECT * FROM usuarios WHERE username = $1 AND password = $2',
            [username, password]
        );

        if (result.rows.length > 0) {
            res.json({ message: 'Login bem-sucedido!' });
        } else {
            res.status(401).json({ error: 'Usuário ou senha inválidos!' });
        }
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

// Iniciar o servidor
app.listen(PORT, () => {
    console.log(`Servidor rodando na porta ${PORT}`);
  });