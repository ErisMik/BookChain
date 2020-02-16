import React from 'react';
import { HashRouter, Switch, Route } from 'react-router-dom';
import { makeStyles } from '@material-ui/core/styles';
import AppBar from '@material-ui/core/AppBar';
import BlocksView from './components/BlocksView';
import BlockView from './components/BlockView';
import Button from '@material-ui/core/Button';
import Link from '@material-ui/core/Link';
import Paper from '@material-ui/core/Paper';
import TextField from '@material-ui/core/TextField';
import Toolbar from '@material-ui/core/Toolbar';
import Typography from '@material-ui/core/Typography';
import UrlsContext from './contexts/UrlsContext';

const useStyles = makeStyles(theme => ({
  root: {
    flexGrow: 1
  },
  menuButton: {
    marginRight: theme.spacing(1)
  },
  menuNavLink: {
    marginRight: theme.spacing(2)
  },
  highlight: {
    color: 'white'
  },
  menuButtonSection: {
    marginLeft: 'auto',
    marginRight: 0
  },
  contentArea: {
    margin: theme.spacing(2),
    marginTop: theme.spacing(10)
  }
}));

function linkToGithub() {
  window.location.href = 'https://github.com/ErisMik/BookChain';
}

function App() {
  const classes = useStyles();
  const [nodeUrl, setNodeUrl] = React.useState('localhost:8000');
  const [signerUrl, setSignerUrl] = React.useState('localhost:8081');

  const handleChangeNodeUrl = event => {
    setNodeUrl(event.target.value);
  };

  const handleChangeSignerUrl = event => {
    setSignerUrl(event.target.value);
  };

  function renderAppBar() {
    return (
      <AppBar position="fixed">
        <Toolbar>
          <Typography
            variant="h5"
            className={[classes.menuNavLink, classes.highlight]}
          >
            <Link href="/#/" color="inherit">
              Bookchain
            </Link>
          </Typography>
          <Typography variant="h6" className={classes.menuNavLink}>
            <Link href="/#/books" color="inherit">
              Books
            </Link>
          </Typography>
          <Typography variant="h6" className={classes.menuNavLink}>
            <Link href="/#/blocks" color="inherit">
              Blocks
            </Link>
          </Typography>
          <Typography variant="h6" className={classes.menuNavLink}>
            <Link href="/#/nodes" color="inherit">
              Nodes
            </Link>
          </Typography>

          <div className={classes.menuButtonSection}>
            <TextField
              id="nodeURL"
              className={classes.menuButton}
              label="Node URL"
              variant="outlined"
              size="small"
              defaultValue={nodeUrl}
              onChange={handleChangeNodeUrl}
            />
            <TextField
              id="signerURL"
              className={classes.menuButton}
              label="Signer URL"
              variant="outlined"
              size="small"
              defaultValue={signerUrl}
              onChange={handleChangeSignerUrl}
            />
            <Button
              variant="contained"
              color="inherit"
              className={classes.menuButton}
            >
              Upload
            </Button>
            <Button
              onClick={() => linkToGithub()}
              color="inherit"
              className={classes.menuButton}
            >
              Github
            </Button>
          </div>
        </Toolbar>
      </AppBar>
    );
  }

  return (
    <div className="App">
      <UrlsContext.Provider value={{ nodeUrl, signerUrl }}>
        <HashRouter>
          {renderAppBar()}

          <Paper elevation={1} className={classes.contentArea}>
            <Switch>
              <Route path="/books">
                <p> Books </p>
              </Route>
              <Route path="/blocks">
                <Switch>
                  <Route path="/blocks/:height">
                    <BlockView />
                  </Route>
                  <Route path="/blocks">
                    <BlocksView />
                  </Route>
                </Switch>
              </Route>
              <Route path="/nodes">
                <p> Nodes </p>
              </Route>
              <Route path="/">
                <p> Home </p>
              </Route>
            </Switch>
          </Paper>
        </HashRouter>
      </UrlsContext.Provider>
    </div>
  );
}

export default App;
