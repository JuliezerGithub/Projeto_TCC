<?php
$databaseFile = 'usuarios.db';

// Conectar ao banco de dados SQLite
$db = new SQLite3($databaseFile);

// Criar a tabela se não existir
$query = "CREATE TABLE IF NOT EXISTS usuarios (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE,
    email TEXT,
    password TEXT
)";
$db->exec($query);

// Verificar ação
$action = $_POST['action'] ?? $_GET['action'] ?? '';

if ($action == 'cadastrar') {
    $username = $_POST['username'];
    $email = $_POST['email'];
    $password = password_hash($_POST['password'], PASSWORD_DEFAULT);

    $stmt = $db->prepare("INSERT INTO usuarios (username, email, password) VALUES (:username, :email, :password)");
    $stmt->bindValue(':username', $username);
    $stmt->bindValue(':email', $email);
    $stmt->bindValue(':password', $password);
    
    if ($stmt->execute()) {
        echo "Usuário cadastrado com sucesso!";
    } else {
        echo "Erro ao cadastrar usuário!";
    }
}

if ($action == 'consultar') {
    $username = $_GET['username'];

    $stmt = $db->prepare("SELECT username, email FROM usuarios WHERE username = :username");
    $stmt->bindValue(':username', $username);
    $result = $stmt->execute();
    $user = $result->fetchArray(SQLITE3_ASSOC);

    echo json_encode($user ?: []);
}

if ($action == 'consultarTodos') {
    $result = $db->query("SELECT username, email FROM usuarios");
    $usuarios = [];

    while ($row = $result->fetchArray(SQLITE3_ASSOC)) {
        $usuarios[] = $row;
    }

    echo json_encode($usuarios);
}

$db->close();
?>
