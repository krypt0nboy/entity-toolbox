<?php

/**
 * @file
 *
 * This file contains formatting functions.
 */

/**
 * Transforms the entity_type machine name to a human readable label.
 * (Eg : "foo_bar" turns to "Foo bar").
 *
 * @param $entity_type
 *   The entity type machine name.
 *
 * @return string
 */
function entity_type2entity_label($entity_type) {
  $label = '';
  $split = explode('_', $entity_type);
  $count = count($split);
  for ($i = 0; $i < $count; $i++) {
    if ($i == 0) {
      $label .= ucfirst($split[0]) . ' ';
    }
    else {
      $label .= ($i + 1) == $count ? $split[$i] : $split[$i] . ' ';
    }
  }

  return $label;
}

/**
 * Transforms the entity_type single machine name to a human readable plural label.
 * (Eg : "foo_city" turns to "Foo cities").
 *
 * @param $entity_type
 *   The entity type machine name.
 *
 * @return string
 */
function entity_type2entity_label_plural($entity_type) {
  $label = '';
  $split = explode('_', $entity_type);
  switch (substr(end($split), (strlen(end($split)) - 1), 1)) {
    case 's':
      $end = end($split) . 'es';
      break;
    case 'y':
      $end = substr_replace(end($split), 'ies', (strlen(end($split)) - 1), 1);
      break;
    default:
      $end = end($split) . 's';
      break;
  }
  $split[count($split) - 1] = $end;
  if (count($split) == 1) {
    return ucfirst(reset($split));
  }
  else {
    if (count($split) > 1) {
      reset($split);
      for ($i = 0; $i < count($split); $i++) {
        switch ($i) {
          case 0:
            $label .= ucfirst($split[$i]) . ' ';
            break;
          case (count($split) - 1):
            $label .= $split[$i];
            break;
          default:
            $label .= $split[$i] . ' ';
            break;
        }
      }
    }
  }

  return $label;
}

/**
 * Transforms the entity_type machine_name into the entity class name.
 * (Eg : "foo_bar" turns to "FooBar").
 *
 * @param $string
 *   The string.
 *
 * @return string
 */
function lowercase2camelcase($string) {
  $split = explode('_', $string);
  $class = '';
  for ($i = 0; $i < count($split); $i++) {
    $class .= ucfirst($split[$i]);
  }

  return $class;
}

/**
 * Transforms the entity_type machine_name into the entity class name.
 * (Eg : "foo_bar" turns to "FooBar").
 *
 * @param $string
 *   The string.
 *
 * @return string
 */
function camelcase2lowercase($string) {
  $regexp = '/(?P<upper>[A-Z])/';
  preg_match_all($regexp, $string, $matches, PREG_OFFSET_CAPTURE);
  $index_mod = 0;
  foreach ($matches['upper'] as $match) {
    $upper         = $match[0];
    $pos           = $match[1] + $index_mod;
    $upper_replace = '_' . strtolower($upper);
    $string        = substr_replace($string, $upper_replace, $pos, 1);
    $index_mod++;
  }

  return $string;
}

/**
 * Transforms the entity_type machine_name into the entity controller class name.
 * (Eg : "foo_bar_type" turns to "FooBarTypeController").
 *
 * @param $entity_type
 *   The entity type machine name.
 *
 * @return string
 */
function entity_type2entity_controller_class($entity_type) {
  $split = explode('_', $entity_type);
  $class = '';
  for ($i = 0; $i < count($split); $i++) {
    $class .= ucfirst($split[$i]);
  }

  return $class . 'Controller';
}

/**
 * Transforms the entity_type machine_name into the entity controller class name.
 * (Eg : "foo_bar_type" turns to "FooBarTypeUIController").
 *
 * @param $entity_type
 *   The entity type machine name.
 *
 * @return string
 */
function entity_type2entity_ui_controller_class($entity_type) {
  $split = explode('_', $entity_type);
  $class = '';
  for ($i = 0; $i < count($split); $i++) {
    $class .= ucfirst($split[$i]);
  }

  return $class . 'UIController';
}

/**
 * Transforms the entity_type machine_name into the entity inline entity form controller name.
 * (Eg : "foo_bar" turns to "FooBarEntityInlineFormController").
 *
 * @param $entity_type
 *   The entity type machine name.
 *
 * @return string
 */
function entity_type2entity_inline_controller_class($entity_type) {
  $split = explode('_', $entity_type);
  $class = '';
  for ($i = 0; $i < count($split); $i++) {
    $class .= ucfirst($split[$i]);
  }

  return $class . 'EntityInlineFormController';
}

/**
 * Transforms the entity_type single machine_name into the entity plural machine_name.
 * (Eg : "foo_bar" turns to "foo_bars").
 *
 * @param string $entity_type
 *   The entity type machine name.
 *
 * @return string
 */
function entity_type_single2plural($entity_type) {
  switch (substr($entity_type, (strlen($entity_type) - 1), 1)) {
    case 's':
      return $entity_type . 'es';
      break;
    case 'y':
      return substr_replace($entity_type, 'ies', (strlen($entity_type) - 1), 1);
      break;
    default:
      return $entity_type . 's';
      break;
  }
}

/**
 * Replace a matching wildcard with a replace pattern.
 *
 * @param string $string
 *   The string to process.
 * @param array  $wildcards
 *   The wildcard to replace.
 * @param array  $variables
 *   The replacing variables.
 *
 * @return mixed
 */
function string_replace_tokens($string, $wildcards = array(), $variables) {
  for ($i = 0; $i < count($wildcards); $i++) {
    $varname = str_replace('%', '', $wildcards[$i]);
    $rgx     = '/' . $wildcards[$i] . '/';
    if (isset($variables[$varname])) {
      switch (gettype($variables[$varname])) {
        case 'boolean':
        case 'integer':
        case 'float':
          $string = $variables[$varname];
          break;
        default:
          $string = preg_replace($rgx, $variables[$varname], $string);
          break;
      }
      $reprocess_var = preg_match_all('/(?P<wildcards>%\w+%)/', $variables[$varname], $matches);
      if ($reprocess_var != 0) {
        for ($ii = 0; $ii < count($matches['wildcards']); $ii++) {
          $var_n = str_replace('%', '', $matches['wildcards'][$ii]);
          if (isset($variables[$var_n])) {
            $rgx_n  = '/' . $matches['wildcards'][$ii] . '/';
            $string = preg_replace($rgx_n, $variables[$var_n], $string);
          }
        }
      }
    }
  }

  return $string;
}

/**
 * Extracts the wildcards from a template string.
 *
 * @param string $string
 *   The template string.
 *
 * @return array
 */
function string_extract_wildcards($string) {
  $regexp = '/(?P<wildcards>%\w+%)/';
  preg_match_all($regexp, $string, $matches);

  return $matches['wildcards'];
}

/**
 * Process a string template.
 *
 * @param string $string
 *   The template string to process.
 * @param array  $variables
 *   The array of replacing variables.
 *
 * @return string
 */
function string_template_process($string, $variables = array()) {
  $wildcards = string_extract_wildcards($string);

  return string_replace_tokens($string, $wildcards, $variables);
}