<?php

/**
 * Class EntityToolboxInfoLabelsModel
 */
class EntityToolboxInfoLabelsRecursiveModel extends EntityToolboxInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'  => 'labels',
        'structure' => array(
          'single'              => array(
            'type'   => 'string',
            'method' => 'buildSingle',
          ),
          'plural'              => array(
            'type'   => 'string',
            'method' => 'buildPlural',
          ),
          'single lowercase'    => array(
            'type'   => 'string',
            'method' => 'buildSingleLowerCase',
          ),
          'plural lowercase'    => array(
            'type'   => 'string',
            'method' => 'buildPluralLowerCase',
          ),
          'machine_name plural' => array(
            'type'   => 'string',
            'method' => 'buildMachineNamePlural',
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}