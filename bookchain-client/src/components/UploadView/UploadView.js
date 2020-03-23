import React from 'react';
import Paper from '@material-ui/core/Paper';
import UrlsContext from 'contexts/UrlsContext';
import TextField from '@material-ui/core/TextField';
import Button from '@material-ui/core/Button';
import { makeStyles } from '@material-ui/core/styles';
import { useTheme } from '@material-ui/core/styles';

const useStyles = makeStyles(theme => ({
  root: {
    width: '100%',
    padding: theme.spacing(2)
  },
  flexContainer: {
    display: 'flex',
    flexDirection: 'column',
    alignItems: 'flex-start'
  },
  uploadSection: {
    margin: theme.spacing(2)
  }
}));

function UploadView(props) {
  const theme = useTheme();
  const classes = useStyles(theme);
  const urls = React.useContext(UrlsContext);

  const [contents, setContents] = React.useState('');

  const handleContentsChange = event => {
    setContents(event.target.value);
  };

  function uploadToNode() {
    const newBookJob = {
      job: {
        data: {
          meta: {},
          contents
        }
      }
    };

    fetch(`http://${urls.nodeUrl}/jobs`, {
      method: 'POST',
      body: JSON.stringify(newBookJob)
    }).then(response => {
      if (!response.ok) {
        console.log('YIKES');
      }
    });
  }

  return (
    <Paper className={`${classes.root} ${classes.flexContainer}`}>
      <TextField
        className={classes.uploadSection}
        label="Book Contents"
        placeholder="Once upon a time..."
        multiline
        value={contents}
        onChange={handleContentsChange}
      />
      <Button
        className={classes.uploadSection}
        onClick={() => uploadToNode()}
        variant="contained"
        color="inherit"
      >
        Upload To Chain
      </Button>
    </Paper>
  );
}

export default UploadView;
