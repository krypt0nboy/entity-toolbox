<?php

/**
 * Class EntityToolboxInfoModelFieldable
 */
class EntityToolboxInfoModelFieldable extends EntityToolboxInfoModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'fieldable'        => array(
            'default' => TRUE,
          ),
          'has_revisions'    => array(
            'default' => TRUE,
          ),
          'has_translations' => array(
            'default' => TRUE,
          ),
          'exportable'       => array(
            'default' => FALSE,
          ),
          'bundle_entity'    => array(
            'type'    => 'string',
            'default' => '%toolbox_info_entity_type%_type'
          ),
          'entity_info'      => array(
            'type'   => 'array',
            'method' => 'buildEntityInfo'
          )
        )
      ), $args
    );
    parent::__construct($args);
  }
}