const express = require('express');
const cors = require('cors');
const app = express();
app.use(express.json());
app.use(cors());
const PORT = process.env.PORT || 3000
app.use("/", require("./src/routes"));
app.listen(PORT);
