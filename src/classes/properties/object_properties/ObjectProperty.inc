<?php

/**
 * Class ObjectProperty
 */
class ObjectProperty extends EntityToolboxPropertyBase {

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'        => 'object',
        'default_php_type'    => 'object',
        'default_drupal_type' => 'struct',
      ),
      $args
    );
    parent::__construct($args);
  }
}