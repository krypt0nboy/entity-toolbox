<?php

/**
 * Class SchemaFieldModel
 */
class SchemaFieldModel extends SchemaRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'type'        => array(
            'type'    => 'string',
            'method'  => '',
            'default' => '',
            'model'   => ''
          ),
          'description' => array(
            'type'    => 'string',
            'method'  => '',
            'default' => '',
            'model'   => ''
          ),
          'not null'    => array(
            'type'    => 'boolean',
            'method'  => '',
            'default' => '',
            'model'   => ''
          ),
          'default'     => array(
            'type'    => 'string',
            'method'  => '',
            'default' => '',
            'model'   => ''
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}