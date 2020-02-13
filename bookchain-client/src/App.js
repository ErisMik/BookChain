import React from 'react';
import { HashRouter, Switch, Route } from 'react-router-dom';
import { makeStyles } from '@material-ui/core/styles';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import Typography from '@material-ui/core/Typography';
import Button from '@material-ui/core/Button';
import Link from '@material-ui/core/Link';

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
  }
}));

function linkToGithub() {
  window.location.href = 'https://github.com/ErisMik/BookChain';
}

function App() {
  const classes = useStyles();

  return (
    <div className="App">
      <HashRouter>
        <AppBar position="static">
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
              <Link href="/#/peers" color="inherit">
                Peers
              </Link>
            </Typography>

            <div className={classes.menuButtonSection}>
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

        <Switch>
          <Route path="/books">
            <p> Books </p>
          </Route>
          <Route path="/blocks">
            <p> Blocks </p>
          </Route>
          <Route path="/peers">
            <p> Peers </p>
          </Route>
          <Route path="/">
            <p> Home </p>
          </Route>
        </Switch>
      </HashRouter>
    </div>
  );
}

export default App;
