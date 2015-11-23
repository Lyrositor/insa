SET HEADING OFF
SET ECHO OFF
SET FEEDBACK OFF
SPOOL '\\servif-home\binomes\IF-B3309\insa\3if\tp\tp-bd_1\grant.sql'

SELECT
  'GRANT SELECT ON ' || Table_Name || ' TO snemmaoui,tcolard;\n' ||
  'GRANT UPDATE ON ' || Table_Name || ' TO snemmaoui,tcolard;' AS Commands
  FROM User_Tables;

SPOOL OUT

@\\servif-home\binomes\IF-B3309\insa\3if\tp\tp-bd_1\grant.sql