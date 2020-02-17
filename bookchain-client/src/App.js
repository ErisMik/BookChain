import React from 'react';
import ApplicationBar from './components/ApplicationBar';
import BlocksView from './components/BlocksView';
import BlockView from './components/BlockView';
import Paper from '@material-ui/core/Paper';
import Theme from './components/Theme';
import UrlsContext from './contexts/UrlsContext';
import { HashRouter, Switch, Route } from 'react-router-dom';
import { makeStyles, ThemeProvider } from '@material-ui/core/styles';

const useStyles = makeStyles(theme => ({
  contentArea: {
    margin: theme.spacing(2),
    marginTop: theme.spacing(10)
  }
}));

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

  return (
    <div className="App">
      <UrlsContext.Provider value={{ nodeUrl, signerUrl }}>
        <ThemeProvider theme={Theme}>
          <HashRouter>
            <ApplicationBar
              {...{ handleChangeNodeUrl, handleChangeSignerUrl }}
            />

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
        </ThemeProvider>
      </UrlsContext.Provider>
    </div>
  );
}

export default App;
