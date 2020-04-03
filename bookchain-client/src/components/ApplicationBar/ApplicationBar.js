import React from 'react';
import AppBar from '@material-ui/core/AppBar';
import Button from '@material-ui/core/Button';
import Link from '@material-ui/core/Link';
import TextField from '@material-ui/core/TextField';
import MenuBookIcon from '@material-ui/icons/MenuBook';
import Toolbar from '@material-ui/core/Toolbar';
import Typography from '@material-ui/core/Typography';
import UrlsContext from 'contexts/UrlsContext';
import { makeStyles } from '@material-ui/core/styles';
import { useTheme } from '@material-ui/core/styles';

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

function ApplicationBar(props) {
  const theme = useTheme();
  const classes = useStyles(theme);
  const { handleChangeNodeUrl, handleChangeSignerUrl } = props;
  const { nodeUrl, signerUrl } = React.useContext(UrlsContext);

  function linkToGithub() {
    window.location.href = 'https://github.com/ErisMik/BookChain';
  }

  function linkToUpload() {
    window.location.href = '/#/upload';
  }

  return (
    <AppBar position="fixed">
      <Toolbar>
        <MenuBookIcon fontSize="large" className={classes.menuNavLink} />
        <Typography
          variant="h5"
          className={`${classes.menuNavLink} ${classes.highlight}`}
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
          <Link href="/#/network" color="inherit">
            Network
          </Link>
        </Typography>

        <div className={classes.menuButtonSection}>
          <TextField
            id="nodeURL"
            className={classes.menuButton}
            label="Node URL"
            variant="outlined"
            size="small"
            color="secondary"
            defaultValue={nodeUrl}
            onChange={handleChangeNodeUrl}
          />
          <TextField
            id="signerURL"
            className={classes.menuButton}
            label="Signer URL"
            variant="outlined"
            size="small"
            color="secondary"
            defaultValue={signerUrl}
            onChange={handleChangeSignerUrl}
          />
          <Button
            onClick={() => linkToUpload()}
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

export default ApplicationBar;
