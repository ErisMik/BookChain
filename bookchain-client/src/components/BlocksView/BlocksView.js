import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Paper from '@material-ui/core/Paper';
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableContainer from '@material-ui/core/TableContainer';
import TableHead from '@material-ui/core/TableHead';
import TablePagination from '@material-ui/core/TablePagination';
import TableRow from '@material-ui/core/TableRow';

const columns = [
  { id: 'blockHeight', label: 'Height', minWidth: 100 },
  { id: 'blockHash', label: 'Hash', minWidth: 200 },
  { id: 'data', label: 'Data', minWidth: 170 }
];

const useStyles = makeStyles({
  root: {
    width: '100%'
  },
  container: {
    maxHeight: '85vh'
  },
  tableDataCell: {
    maxWidth: '80vh',
    whiteSpace: 'nowrap',
    overflow: 'hidden',
    textOverflow: 'ellipsis'
  }
});

function BlocksView(props) {
  const classes = useStyles();
  const [blocks, setBlocks] = React.useState([]);
  const [maxBlocks, setMaxBlocks] = React.useState([]);
  const [page, setPage] = React.useState(0);
  const [rowsPerPage, setRowsPerPage] = React.useState(25);

  React.useEffect(() => {
    fetch(`http://localhost:8000/blocks?page=${page}&page_size=${rowsPerPage}`)
      .then(result => result.json())
      .then(blocks => {
        setBlocks(blocks);
      });

    fetch(`http://localhost:8000/blocks/latest`)
      .then(result => result.json())
      .then(block => {
        setMaxBlocks(block.blockHeight);
      });
  }, [page, rowsPerPage]);

  const handleChangePage = (event, newPage) => {
    setPage(newPage);
  };

  const handleChangeRowsPerPage = event => {
    setRowsPerPage(+event.target.value);
    setPage(0);
  };

  function renderRows() {
    return blocks.map(block => {
      return (
        <TableRow hover role="checkbox" tabIndex={-1} key={block.blockHeight}>
          {columns.map(column => {
            const value = block[column.id];
            return (
              <TableCell
                key={column.id}
                align={column.align}
                className={classes.tableDataCell}
              >
                {value}
              </TableCell>
            );
          })}
        </TableRow>
      );
    });
  }

  return (
    <Paper className={classes.root}>
      <TableContainer className={classes.container}>
        <Table stickyHeader size="small" aria-label="blocks-table">
          <TableHead>
            <TableRow>
              {columns.map(column => (
                <TableCell
                  key={column.id}
                  align={column.align}
                  style={{ minWidth: column.minWidth }}
                >
                  {column.label}
                </TableCell>
              ))}
            </TableRow>
          </TableHead>
          <TableBody>{renderRows()}</TableBody>
        </Table>
      </TableContainer>
      <TablePagination
        rowsPerPageOptions={[10, 25, 100, 500]}
        component="div"
        count={maxBlocks}
        rowsPerPage={rowsPerPage}
        page={page}
        onChangePage={handleChangePage}
        onChangeRowsPerPage={handleChangeRowsPerPage}
      />
    </Paper>
  );
}

export default BlocksView;
