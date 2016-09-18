<?php

/**
 * Class EntityToolboxInfoTablesModel
 */
class EntityToolboxInfoTablesModel extends EntityToolboxInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'  => 'tables',
        'structure' => array(
          'base'              => array(
            'type'    => 'string',
            'default' => '%toolbox_info_entity_type%',
          ),
          'revision'          => array(
            'type'    => 'string',
            'default' => '%toolbox_info_entity_type%_revision',
          ),
          'relation'          => array(
            'type'    => 'array',
            'method'  => 'buildRelationTables',
            'default' => array(),
          ),
          'relation_revision' => array(
            'type'    => 'array',
            'method'  => 'buildRelationRevisionTables',
            'default' => array(),
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}