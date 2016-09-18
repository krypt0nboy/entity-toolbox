<?php

/**
 * Class MachineNameProperty
 */
class MachineNameProperty extends VarcharProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'        => 'machine_name',
        'default_drupal_type' => 'token',
        'default_forms'       => array(
          'edit'   => array(
            'widget' => 'machine_name',
            'source' => '',
          ),
          'inline' => array(
            'widget' => 'machine_name',
            'source' => '',
          ),
        ),
        'default_value'       => array(
          'filter' => array(
            '\W'           => '_',
            '[^[:alnum:]]' => '_',
            '[[:upper:]]'  => '[[:lower:]]',
          )
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}

//$this->setFilterChars(array());
