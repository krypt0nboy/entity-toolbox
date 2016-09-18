<?php

/**
 * @file
 *
 * This file should contains all the callbacks and custom function for the bar and bar_type entity.
 *
 */

/**
 * Determines whether the given user has access to a bar.
 *
 * @param string $op
 *   The operation being performed. One of 'view', 'update', 'create', 'delete'
 *   or just 'edit' (being the same as 'create' or 'update').
 * @param object $bar
 *   Optionally a bar or a bar type to check access for.
 *   If nothing is given, access for all bars is determined.
 * @param object $account
 *   The user to check for. Leave it to NULL to check for the global user.
 *
 * @return bool
 *   Whether access is allowed or not.
 */
function bar_access($op, $bar = NULL, $account = NULL) {
  global $user;
  if ($user->uid == 1) {
    return TRUE;
  }
  if (user_access('administer bar', $account)) {
    return TRUE;
  }
  if (isset($bar) && $type_name = $bar->type) {
    $op = ($op == 'view') ? 'view' : 'edit';
    if (user_access("$op any $type_name bar", $account)) {
      return TRUE;
    }
  }

  $access = module_invoke_all('bar_access', $op, $bar, $account);
  if (in_array(FALSE, $access, TRUE)) {
    return FALSE;
  }
  elseif (in_array(TRUE, $access, TRUE)) {
    return TRUE;
  }

  return FALSE;
}